//C++ includes
#include <stdexcept>
#include <vector>

//SHOGUN includes
#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/CollisionUtility.hpp>

namespace sg
{
    Entity::Entity() :
    sf::Transformable()
    {
        this->owner = NULL;
        this->isCollidable = true;
        this->deletion = false;
    }

    Entity::Entity(bool setCollidable) :
    sf::Transformable()
    {
        this->owner = NULL;
        this->isCollidable = setCollidable;
        this->deletion = false;
    }

    Entity::Entity(const Entity &another) :
    sf::Transformable()
    {
        this->deletion = another.deletion;
        this->possessions = another.possessions;
        this->owner = another.owner;
        this->isCollidable = another.isCollidable;
        for (Component *com : another.components)
        {
            this->components.push_back(new Component(*(com->d), *(com->t)));
        }
    }

    void Entity::operator= (const Entity &another)
    {
        this->deletion = another.deletion;
        this->possessions = another.possessions;
        this->owner = another.owner;
        this->isCollidable = another.isCollidable;
        for (Component *com : this->components)
        {
            delete com;
        }
        for (Component *com : another.components)
        {
            this->components.push_back(new Component(*(com->d), *(com->t)));
        }
    }

    Entity::~Entity()
    {
        for (Component *com : this->components)
        {
            delete com;
        }
    }

    bool Entity::collides(Entity &e, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f> &collisionMap)
    {
        bool isCollides = false;
        if (this->isCollidable && e.getIsCollidable())
        {
            sf::FloatRect bounds0 = this->getSurfaceBounds(true);
            bounds0.width += bounds0.left;
            bounds0.height += bounds0.top;

            sf::FloatRect bounds1 = e.getSurfaceBounds(true);
            bounds1.width += bounds1.left;
            bounds1.height += bounds1.top;

            if (bounds0.left <= bounds1.width &&
                bounds0.width >= bounds1.left &&
                bounds0.top <= bounds1.height &&
                bounds0.height >= bounds1.top)
            {
                sf::Transform trans0 = sf::Transform::Identity;
                sf::Transform trans1 = sf::Transform::Identity;
                this->getGlobalTransform(trans0);
                e.getGlobalTransform(trans1);

                for (uint64_t i = 0; i < this->getNumOfComponents(); ++i)
                {
                    for (uint64_t j = 0; j < e.getNumOfComponents(); ++j)
                    {
                        const sf::Transformable *t0 = this->getComponent(i).second;
                        const AnimatedSprite *as0 = dynamic_cast<const AnimatedSprite *>(t0);
                        if (as0 != NULL)
                        {
                            t0 = as0->getFrameBound(as0->getFrameIndex());
                        }
                        if (t0 == NULL)
                        {
                            continue;
                        }

                        const sf::Transformable *t1 = e.getComponent(j).second;
                        const AnimatedSprite *as1 = dynamic_cast<const AnimatedSprite *>(t1);
                        if (as1 != NULL)
                        {
                            t1 = as1->getFrameBound(as1->getFrameIndex());
                        }
                        if (t1 == NULL)
                        {
                            continue;
                        }

                        if (t0 != NULL && t1 != NULL)
                        {
                            sf::Vector2f collisionVector(0.0f, 0.0f);
                            bool componentCollides = CollisionUtility::inst().collides(*t0, *t1, trans0, trans1, collisionVector);
                            if (componentCollides)
                            {
                                collisionMap[std::make_pair(i, j)] = collisionVector;
                                isCollides = componentCollides;
                            }
                        }
                    }
                }
            }
        }

        return isCollides;
    }

    bool Entity::getIsCollidable() const
    {
        return this->isCollidable;
    }

    void Entity::setIsCollidable(bool flag)
    {
        this->isCollidable = flag;
    }

    bool Entity::getDeletionStatus() const
    {
        return deletion;
    }

    void Entity::setDeletionStatus(bool newDeletionStatus)
    {
        this->deletion = newDeletionStatus;
    }

    std::vector<Component *>::size_type Entity::getNumOfComponents() const
    {
        return this->components.size();
    }

    std::pair<const sf::Drawable *, const sf::Transformable *> Entity::getComponent(uint32_t idx) const
    {
        if (idx >= this->getNumOfComponents())
        {
            return std::pair<const sf::Drawable *, const sf::Transformable *>(NULL, NULL);
        }

        return std::pair<const sf::Drawable *, const sf::Transformable *>(this->components[idx]->d,
                                                                          this->components[idx]->t);
    }

    std::vector<Entity *>::size_type Entity::getNumOfPossessions() const
    {
        return this->possessions.size();
    }

    const Entity *Entity::getPossession(uint32_t idx) const
    {
        if (idx >= this->getNumOfPossessions())
        {
            return NULL;
        }

        return this->possessions[idx];
    }

    const Entity *Entity::getOwner() const
    {
        return this->owner;
    }

    std::pair<sf::Vector2f, float> Entity::getGlobalTransform(sf::Transform &globalTransform) const
    {
        sf::Vector2f globalScale;
        globalScale.x = 1.0f;
        globalScale.y = 1.0f;
        float globalRotation = 0.0f;
        std::stack<const sf::Transform *> transforms;
        const Entity *currentAncestor = this;
        while (currentAncestor != NULL)
        {
            globalScale.x *= currentAncestor->getScale().x;
            globalScale.y *= currentAncestor->getScale().y;
            globalRotation += currentAncestor->getRotation();
            transforms.push(&currentAncestor->getTransform());
            currentAncestor = currentAncestor->getOwner();
        }
        while (!transforms.empty())
        {
            globalTransform *= (*transforms.top());
            transforms.pop();
        }

        return std::pair<sf::Vector2f, float>(globalScale, globalRotation);
    }

    sf::Vector2f Entity::getGlobalPosition() const
    {
        if (this->getOwner())
        {
            sf::Transform trans = sf::Transform::Identity;
            this->getOwner()->getGlobalTransform(trans);

            return trans.transformPoint(this->getPosition());
        }

        return this->getPosition();
    }

    float Entity::getGlobalRotation() const
    {
        float globalRotation = 0.0f;
        const Entity *currentAncestor = this;
        while (currentAncestor != NULL)
        {
            globalRotation += currentAncestor->getRotation();
            currentAncestor = currentAncestor->getOwner();
        }

        return globalRotation;
    }

    sf::Vector2f Entity::getGlobalScale() const
    {
        sf::Vector2f globalScale;
        globalScale.x = 1.0f;
        globalScale.y = 1.0f;
        const Entity *currentAncestor = this;
        while (currentAncestor != NULL)
        {
            globalScale.x *= currentAncestor->getScale().x;
            globalScale.y *= currentAncestor->getScale().y;
            currentAncestor = currentAncestor->getOwner();
        }

        return globalScale;
    }

    void Entity::setGlobalPosition(float x, float y)
    {
        this->setGlobalPosition(sf::Vector2f(x, y));
    }

    void Entity::setGlobalPosition(const sf::Vector2f &position)
    {
        if (this->getOwner())
        {
            sf::Transform trans = sf::Transform::Identity;
            this->getOwner()->getGlobalTransform(trans);
            this->setPosition(trans.getInverse().transformPoint(position));
        }
        else
        {
            this->setPosition(position);
        }
    }

    void Entity::moveGlobally(float offsetX, float offsetY, bool withScale, bool withRotation)
    {
        this->moveGlobally(sf::Vector2f(offsetX, offsetY), withScale, withRotation);
    }

    void Entity::moveGlobally(const sf::Vector2f &offset, bool withScale, bool withRotation)
    {
        if (this->getOwner())
        {
            sf::Transform trans = sf::Transform::Identity;
            if (withScale)
            {
                trans.scale(this->getOwner()->getGlobalScale());
            }
            if (withRotation)
            {
                trans.rotate(this->getOwner()->getGlobalRotation());
            }
            this->move(trans.getInverse().transformPoint(offset));
        }
        else
            this->move(offset);
    }

    void Entity::setGlobalRotation(float angle, bool useDeg)
    {
        if (!useDeg)
        {
            angle *= (180.0f / M_PI);//If angle is not degs then make it degs
        }
        if (this->getOwner())
        {
            float transAngle = this->getOwner()->getGlobalRotation();
            //The trans angle is the angle that the owner is
            //transforming this entity by. If we are globally setting
            //the angle to 90 and the trans ange is already at 90 then
            //we want the entity's contrabution to its total rotation
            //to be 0 because the owner is alrady contributing all 90
            //degrees
            this->setRotation(angle - transAngle);
        }
        else
        {
            this->setRotation(angle);
        }
    }

    void Entity::rotateGlobally(float angle, bool useDeg)
    {
        if (!useDeg)
        {
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs
        }
        this->rotate(angle);
    }

    void Entity::setGlobalScale(float factorX, float factorY)
    {
        this->setGlobalScale(sf::Vector2f(factorX, factorY));
    }

    void Entity::setGlobalScale(const sf::Vector2f &factor)
    {
        if (this->getOwner())
        {
            sf::Vector2f transScale = this->getOwner()->getGlobalScale();
            this->setScale(factor.x/transScale.x, factor.y/transScale.y);
        }
        else
        {
            this->setScale(factor);
        }
    }

    void Entity::scaleGlobally(float factorX, float factorY)
    {
        this->scale(factorX, factorY);
    }

    void Entity::scaleGlobally(const sf::Vector2f &factor)
    {
        this->scale(factor);
    }

    void Entity::setOriginComponent(uint32_t idx, const sf::Vector2f &origin)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->setOrigin(origin);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->setOrigin(origin);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->setOrigin(origin);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->setOrigin(origin);
        }
    }

    void Entity::setPositionComponent(uint32_t idx, const sf::Vector2f &position)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->setPosition(position);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->setPosition(position);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->setPosition(position);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->setPosition(position);
        }
    }

    void Entity::moveComponent(uint32_t idx, const sf::Vector2f &offset)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->move(offset);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->move(offset);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->move(offset);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->move(offset);
        }
    }

    void Entity::setRotationComponent(uint32_t idx, float angle, bool useDeg)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (!useDeg)
        {
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->setRotation(angle);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->setRotation(angle);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->setRotation(angle);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->setRotation(angle);
        }
    }

    void Entity::rotateComponent(uint32_t idx, float angle, bool useDeg)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (!useDeg)
        {
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->rotate(angle);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->rotate(angle);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->rotate(angle);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->rotate(angle);
        }
    }

    void Entity::setScaleComponent(uint32_t idx, const sf::Vector2f &factor)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->setScale(factor);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->setScale(factor);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->setScale(factor);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->setScale(factor);
        }
    }

    void Entity::scaleComponent(uint32_t idx, const sf::Vector2f &factor)
    {
        if (idx >= this->getNumOfComponents())
        {
            return;
        }

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
        {
            s->scale(factor);
        }
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
        {
            sh->scale(factor);
        }
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
        {
            t->scale(factor);
        }

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) &&
            this->components[idx]->t != NULL)
        {
            this->components[idx]->t->scale(factor);
        }
    }

    void Entity::expandSurfaceBounds(sf::FloatRect &bounds, sf::FloatRect br) const
    {
        if (br.left < bounds.left)
        {
            bounds.left = br.left;
        }
        if (br.top < bounds.top)
        {
            bounds.top = br.top;
        }
        if ((br.left + br.width) > bounds.width)
        {
            bounds.width = (br.left + br.width);
        }
        if ((br.top + br.height) > bounds.height)
        {
            bounds.height = (br.top + br.height);
        }
    }

    sf::FloatRect Entity::getSurfaceBounds(bool useGlobal) const
    {
        if (this->components.size() == 0)
        {
            sf::FloatRect zeroCompBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (useGlobal)
            {
                sf::Transform transform = sf::Transform::Identity;
                this->getGlobalTransform(transform);
                zeroCompBounds = transform.transformRect(zeroCompBounds);
            }

            return zeroCompBounds;
        }

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds = sf::FloatRect(inf, inf, -inf, -inf);
        for (const auto &it : this->components)
        {
            const sf::Transformable *t = it->t;
            if (!t)
            {
                continue;
            }
            if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t))
            {
                t = as->getFrameBound(as->getFrameIndex());
            }
            if (!t)
            {
                continue;
            }

            sf::FloatRect currentBounds;
            if (const sf::Sprite *s = dynamic_cast<const sf::Sprite *>(t))
            {
                if (useGlobal)
                {
                    currentBounds = s->getGlobalBounds();
                }
                else
                {
                    currentBounds = s->getLocalBounds();
                }
            }
            else if (const sf::Shape *sh = dynamic_cast<const sf::Shape *>(t))
            {
                if (useGlobal)
                {
                    currentBounds = sh->getGlobalBounds();
                }
                else
                {
                    currentBounds = sh->getLocalBounds();
                }
            }
            else if (const sf::Text *tx = dynamic_cast<const sf::Text *>(t))
            {
                if (useGlobal)
                {
                    currentBounds = tx->getGlobalBounds();
                }
                else
                {
                    currentBounds = tx->getLocalBounds();
                }
            }
            else
            {
                continue;
            }

            if (useGlobal)
            {
                sf::Transform globalTransform = sf::Transform::Identity;
                this->getGlobalTransform(globalTransform);
                currentBounds = globalTransform.transformRect(currentBounds);
            }
            this->expandSurfaceBounds(bounds, currentBounds);
        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;
    }

    sf::FloatRect Entity::getTextureBounds(bool useGlobal) const
    {
        if (this->components.size() == 0)
        {
            sf::FloatRect zeroCompBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (useGlobal)
            {
                sf::Transform transform = sf::Transform::Identity;
                this->getGlobalTransform(transform);
                zeroCompBounds = transform.transformRect(zeroCompBounds);
            }

            return zeroCompBounds;
        }

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (const auto &it : this->components)
        {
            sf::FloatRect currentBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(it->d))
            {
                if (useGlobal)
                {
                    currentBounds = s->getGlobalBounds();
                }
                else
                {
                    currentBounds = s->getLocalBounds();
                }
            }
            else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(it->d))
            {
                if (useGlobal)
                {
                    currentBounds = sh->getGlobalBounds();
                }
                else
                {
                    currentBounds = sh->getLocalBounds();
                }
            }
            else if (sf::Text *t = dynamic_cast<sf::Text *>(it->d))
            {
                if (useGlobal)
                {
                    currentBounds = t->getGlobalBounds();
                }
                else
                {
                    currentBounds = t->getLocalBounds();
                }
            }
            else if (sf::VertexArray *va = dynamic_cast<sf::VertexArray *>(it->d))
            {
                currentBounds = va->getBounds();
            }
            else
            {
                continue;
            }

            if (useGlobal)
            {
                sf::Transform globalTransform = sf::Transform::Identity;
                this->getGlobalTransform(globalTransform);
                currentBounds = globalTransform.transformRect(currentBounds);
            }
            this->expandSurfaceBounds(bounds, currentBounds);
        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;
    }

    sf::FloatRect Entity::getTotalBounds(bool useGlobal) const
    {
        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds = sf::FloatRect(inf, inf, -inf, -inf);

        this->expandSurfaceBounds(bounds, this->getSurfaceBounds(useGlobal));
        this->expandSurfaceBounds(bounds, this->getTextureBounds(useGlobal));
        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;
    }

    bool Entity::isPointInSurfaceBounds(sf::Vector2f &point, bool useGlobal) const
    {
        sf::FloatRect surfBounds = this->getSurfaceBounds(useGlobal);
        return (point.x >= surfBounds.left) &&
               (point.x <= (surfBounds.left + surfBounds.width)) &&
               (point.y >= surfBounds.top) &&
               (point.y <= (surfBounds.top + surfBounds.height));
    }

    bool Entity::isPointInTextureBounds(sf::Vector2f &point, bool useGlobal) const
    {
        sf::FloatRect textBounds = this->getTextureBounds(useGlobal);
        return (point.x >= textBounds.left) &&
               (point.x <= (textBounds.left + textBounds.width)) &&
               (point.y >= textBounds.top) &&
               (point.y <= (textBounds.top + textBounds.height));
    }

    bool Entity::isPointInTotalBounds(sf::Vector2f &point, bool useGlobal) const
    {
        return (this->isPointInSurfaceBounds(point, useGlobal) ||
                this->isPointInTextureBounds(point, useGlobal));
    }

    std::vector<Component *>::size_type Entity::addDrawable(sf::Drawable &newDrawable,
                                                            bool makeTransformable)
    {
        sf::Transformable *t = NULL;
        if (makeTransformable && (t = dynamic_cast<sf::Transformable *>(&newDrawable)))
        {
            return this->addComponent(newDrawable, *t);
        }

        Component *c = new Component();
        c->d = &newDrawable;
        c->t = t;
        this->components.push_back(c);

        return (this->getNumOfComponents() - 1);
    }

    std::vector<Component *>::size_type Entity::addTransformable(sf::Transformable &newTransformable,
                                                                 bool makeDrawable)
    {
        sf::Drawable *d = NULL;
        if (makeDrawable && (d = dynamic_cast<sf::Drawable *>(&newTransformable)))
        {
            return this->addComponent(*d, newTransformable);
        }

        if (dynamic_cast<Entity *>(&newTransformable))
        {
            throw std::invalid_argument("Component\'s sf::Transfromable cannot be an Entity");
        }

        Component *c = new Component();
        c->d = d;
        c->t = &newTransformable;
        this->components.push_back(c);

        return (this->getNumOfComponents() - 1);
    }

    std::vector<Component *>::size_type Entity::addComponent(sf::Drawable &newDrawable,
                                                             sf::Transformable &newTransformable)
    {
        if (dynamic_cast<Entity *>(&newTransformable))
        {
            throw std::invalid_argument("Component\'s sf::Transfromable cannot be an Entity");
        }

        this->components.push_back(new Component(newDrawable, newTransformable));

        return (this->getNumOfComponents() - 1);
    }

    std::pair<sf::Drawable *, sf::Transformable *> Entity::removeComponent(uint32_t idx)
    {
        if (idx >= this->getNumOfComponents())
        {
            return std::pair<sf::Drawable *, sf::Transformable *>(NULL, NULL);
        }

        Component *r = this->components[idx];
        sf::Drawable *d = r->d;
        sf::Transformable *t = r->t;
        this->components.erase(this->components.begin() + idx);
        delete r;
        r = NULL;

        return std::pair<sf::Drawable *, sf::Transformable *>(d, t);

    }

    std::vector<Entity *>::size_type Entity::addPossession(Entity &newPossession, bool adjustForRelativeChange)
    {

        if (newPossession.owner != NULL)
        {
            return (this->getNumOfComponents() - 1);
        }

        const Entity *currentAncestor = this;
        while (currentAncestor != NULL)
        {
            if (dynamic_cast<const void *>(currentAncestor) == dynamic_cast<void *>(&newPossession))
            {
                return (this->getNumOfComponents() - 1);
            }

            currentAncestor = currentAncestor->getOwner();
        }

        if (adjustForRelativeChange)
        {
            sf::Transform trans = sf::Transform::Identity;
            std::pair<sf::Vector2f, float> transPair = this->getGlobalTransform(trans);
            newPossession.scale(1.0f/transPair.first.x, 1.0f/transPair.first.y);
            newPossession.rotate(-transPair.second);
            newPossession.setPosition(trans.getInverse().transformPoint(newPossession.getPosition()));
        }

        newPossession.owner = this;
        this->possessions.push_back(&newPossession);

        return (this->getNumOfComponents() - 1);
    }

    Entity *Entity::removePossession(uint32_t idx, bool adjustForRelativeChange)
    {
        if (idx >= this->getNumOfPossessions())
        {
            return NULL;
        }

        Entity *r = this->possessions[idx];
        this->possessions.erase(this->possessions.begin() + idx);
        if (adjustForRelativeChange)
        {
            sf::Transform trans = sf::Transform::Identity;
            std::pair<sf::Vector2f, float> transPair = this->getGlobalTransform(trans);
            r->setPosition(trans.transformPoint(r->getPosition()));
            r->rotate(transPair.second);
            r->scale(transPair.first.x, transPair.first.y);
        }
        r->owner = NULL;

        return r;
    }

    int Entity::removePossession(Entity &possessionToRemove, bool adjustForRelativeChange)
    {
        uint32_t i;
        for (i = 0; i < this->getNumOfPossessions(); ++i)
        {
            if (dynamic_cast<void *>(this->possessions[i]) == dynamic_cast<void *>(&possessionToRemove))
            {
                if (dynamic_cast<void *>(this->removePossession(i, adjustForRelativeChange)) == dynamic_cast<void *>(&possessionToRemove))
                {
                    return i;
                }

                return -1;
            }
        }

        return -1;
    }
}
