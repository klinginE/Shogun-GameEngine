//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"Entity.hpp"

namespace sg {

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

    Entity::~Entity() {

        this->owner = NULL;
        this->isCollidable = false;
        this->deletion = false;
        for (const auto &it : this->components)
            delete it;
        this->components.clear();
        this->possessions.clear();

    }

    bool Entity::collides(sg::Entity &e) {

        if (!this->isCollidable || !e.getIsCollidable())
            return false;

        bool isCollides = false;
        std::vector<sf::Vector2f> collisionVectors0;
        std::vector<sf::Vector2f> collisionVectors1;
        sf::Transform trans0 = sf::Transform::Identity;
        sf::Transform trans1 = sf::Transform::Identity;
        this->getGlobalTransform(trans0);
        e.getGlobalTransform(trans1);
        for (const auto &it : this->components)
            for (uint32_t i = 0; i < e.getNumOfComponents(); i++) {

                const sf::Transformable *t0 = it->t;
                if (!t0)
                    continue;
                if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t0))
                    t0 = as->getFrameBound(as->getFrameIndex());
                if (!t0)
                    continue;

                const sf::Transformable *t1 = e.getComponent(i).second;
                if (!t1)
                    continue;
                if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t1))
                    t1 = as->getFrameBound(as->getFrameIndex());
                if (!t1)
                    continue;

                sf::RectangleShape tempRs0;
                BoundingShape tempShape0;
                sf::ConvexShape tempConvex0;
                sf::CircleShape tempCircle0;
                const BoundingShape *s0 = NULL;
                if (const BoundingShape *bs = dynamic_cast<const BoundingShape *>(t0))
                    s0 = bs;
                else if (const sf::Shape *sh = dynamic_cast<const sf::Shape *>(t0)) {

                    if (const sf::CircleShape *cs = dynamic_cast<const sf::CircleShape *>(sh)) {

                        tempCircle0.setOrigin(cs->getOrigin());
                        tempCircle0.setPosition(cs->getPosition());
                        tempCircle0.setRotation(cs->getRotation());
                        tempCircle0.setScale(cs->getScale());
                        tempCircle0.setRadius(cs->getRadius());
                        tempShape0.addShape(tempCircle0);

                    }
                    else {
                    
                        tempConvex0.setOrigin(sh->getOrigin());
                        tempConvex0.setPosition(sh->getPosition());
                        tempConvex0.setRotation(sh->getRotation());
                        tempConvex0.setScale(sh->getScale());
                        tempConvex0.setPointCount(sh->getPointCount());
                        for (uint32_t pi = 0; pi < sh->getPointCount(); ++pi)
                            tempConvex0.setPoint(pi, sh->getPoint(pi));
                        tempShape0.addShape(tempConvex0);

                    }
                    s0 = &tempShape0;

                }
                else {

                    sf::FloatRect t0Bounds;
                    if (const sf::Sprite *s = dynamic_cast<const sf::Sprite *>(t0))
                        t0Bounds = s->getLocalBounds();
                    else if (const sf::Text *t = dynamic_cast<const sf::Text *>(t0))
                        t0Bounds = t->getLocalBounds();
                    else
                        continue;

                    tempRs0.setSize(sf::Vector2f(t0Bounds.width, t0Bounds.height));
                    tempRs0.setOrigin(t0->getOrigin());
                    tempRs0.setPosition(sf::Vector2f(t0->getPosition().x + t0Bounds.left, t0->getPosition().y + t0Bounds.top));
                    tempRs0.setRotation(t0->getRotation());
                    tempRs0.setScale(t0->getScale());
                    tempShape0.addShape(tempRs0);
                    s0 = &tempShape0;

                }

                sf::RectangleShape tempRs1;
                BoundingShape tempShape1;
                sf::ConvexShape tempConvex1;
                sf::CircleShape tempCircle1;
                const BoundingShape *s1 = NULL;
                if (const BoundingShape *bs = dynamic_cast<const BoundingShape *>(t1))
                    s1 = bs;
                else if (const sf::Shape *sh = dynamic_cast<const sf::Shape *>(t1)) {

                    if (const sf::CircleShape *cs = dynamic_cast<const sf::CircleShape *>(sh)) {

                        tempCircle1.setOrigin(cs->getOrigin());
                        tempCircle1.setPosition(cs->getPosition());
                        tempCircle1.setRotation(cs->getRotation());
                        tempCircle1.setScale(cs->getScale());
                        tempCircle1.setRadius(cs->getRadius());
                        tempShape1.addShape(tempCircle1);

                    }
                    else {
                    
                        tempConvex1.setOrigin(sh->getOrigin());
                        tempConvex1.setPosition(sh->getPosition());
                        tempConvex1.setRotation(sh->getRotation());
                        tempConvex1.setScale(sh->getScale());
                        tempConvex1.setPointCount(sh->getPointCount());
                        for (uint32_t pi = 0; pi < sh->getPointCount(); ++pi)
                            tempConvex1.setPoint(pi, sh->getPoint(pi));
                        tempShape1.addShape(tempConvex1);

                    }
                    s1 = &tempShape1;

                }
                else {

                    sf::FloatRect t1Bounds;
                    if (const sf::Sprite *s = dynamic_cast<const sf::Sprite *>(t1))
                        t1Bounds = s->getLocalBounds();
                    else if (const sf::Text *t = dynamic_cast<const sf::Text *>(t1))
                        t1Bounds = t->getLocalBounds();
                    else
                        continue;

                    tempRs1.setSize(sf::Vector2f(t1Bounds.width, t1Bounds.height));
                    tempRs1.setOrigin(t1->getOrigin());
                    tempRs1.setPosition(sf::Vector2f(t1->getPosition().x + t1Bounds.left, t1->getPosition().y + t1Bounds.top));
                    tempRs1.setRotation(t1->getRotation());
                    tempRs1.setScale(t1->getScale());
                    tempShape1.addShape(tempRs1);
                    s1 = &tempShape1;

                }

                if (s0 != NULL && s1 != NULL) {

                    sf::FloatRect bounds0 = s0->getGlobalBounds();
                    bounds0 = trans0.transformRect(bounds0);
                    bounds0.width += bounds0.left;
                    bounds0.height += bounds0.top;
                    sf::FloatRect bounds1 = s1->getGlobalBounds();
                    bounds1 = trans1.transformRect(bounds1);
                    bounds1.width += bounds0.left;
                    bounds1.height += bounds1.top;
                    if (bounds0.left <= bounds1.width &&
                        bounds0.width >= bounds1.left &&
                        bounds0.top <= bounds1.height &&
                        bounds0.height >= bounds1.top &&
                        s0->collides((*s1), collisionVectors0, trans0, trans1))
                        isCollides = true;

                }

            }

        if (isCollides) {

            for (auto &itt : collisionVectors0)
                collisionVectors1.push_back(-itt);
            this->handleCollision(e, collisionVectors0);
            e.handleCollision(*this, collisionVectors1);

        }

        return isCollides;

    }

    bool Entity::getIsCollidable() const {

        return this->isCollidable;

    }

    void Entity::setIsCollidable(bool flag) {

        this->isCollidable = flag;

    }

    bool Entity::getDeletionStatus() {

        return deletion;

    }

    void Entity::setDeletionStatus(bool newDeletionStatus) {

        deletion = newDeletionStatus;

    }

    std::vector<Component *>::size_type Entity::getNumOfComponents() const {

        return this->components.size();

    }

    std::pair<const sf::Drawable *, const sf::Transformable *> Entity::getComponent(uint32_t idx) const {

        if (idx >= this->getNumOfComponents())
            return std::pair<const sf::Drawable *, const sf::Transformable *>(NULL, NULL);
        return std::pair<const sf::Drawable *, const sf::Transformable *>(this->components[idx]->d, this->components[idx]->t);

    }

    std::vector<Entity *>::size_type Entity::getNumOfPossessions() const {

        return this->possessions.size();

    }

    const Entity *Entity::getPossession(uint32_t idx) const {

        if (idx >= this->getNumOfPossessions())
            return NULL;
        return this->possessions[idx];

    }

    const Entity *Entity::getOwner() const {

        return this->owner;

    }

    void Entity::getGlobalTransform(sf::Transform &globalTransform) const {

        std::stack<const sf::Transform *> transforms;
        const Entity *currentAncestor = this;
        while (currentAncestor != NULL) {

            transforms.push(&currentAncestor->getTransform());
            currentAncestor = currentAncestor->getOwner();

        }
        while (!transforms.empty()) {

            globalTransform *= (*transforms.top());
            transforms.pop();

        }

    }

    void Entity::setOriginComponent(uint32_t idx, const sf::Vector2f &origin) {

        if (idx >= this->getNumOfComponents())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->setOrigin(origin);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->setOrigin(origin);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->setOrigin(origin);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->setOrigin(origin);

    }

    void Entity::setPositionComponent(uint32_t idx, const sf::Vector2f &position) {

        if (idx >= this->getNumOfComponents())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->setPosition(position);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->setPosition(position);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->setPosition(position);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->setPosition(position);

    }

    void Entity::moveComponent(uint32_t idx, const sf::Vector2f &offset) {

        if (idx >= this->getNumOfComponents())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->move(offset);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->move(offset);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->move(offset);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->move(offset);

    }

    void Entity::setRotationComponent(uint32_t idx, float angle, bool useDeg) {

        if (idx >= this->getNumOfComponents())
            return;
        if (!useDeg)
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->setRotation(angle);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->setRotation(angle);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->setRotation(angle);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->setRotation(angle);

    }

    void Entity::rotateComponent(uint32_t idx, float angle, bool useDeg) {

        if (idx >= this->getNumOfComponents())
            return;
        if (!useDeg)
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->rotate(angle);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->rotate(angle);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->rotate(angle);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->rotate(angle);

    }

    void Entity::setScaleComponent(uint32_t idx, const sf::Vector2f &factor) {

        if (idx >= this->getNumOfComponents())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->setScale(factor);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->setScale(factor);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->setScale(factor);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->setScale(factor);

    }

    void Entity::scaleComponent(uint32_t idx, const sf::Vector2f &factor) {

        if (idx >= this->getNumOfComponents())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->components[idx]->d))
            s->scale(factor);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->components[idx]->d))
            sh->scale(factor);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->components[idx]->d))
            t->scale(factor);

        if (dynamic_cast<void *>(this->components[idx]->d) != dynamic_cast<void *>(this->components[idx]->t) && this->components[idx]->t != NULL)
            this->components[idx]->t->scale(factor);

    }

    void Entity::expandSurfaceBounds(sf::FloatRect &bounds, sf::FloatRect br) const {

        if (br.left < bounds.left)
            bounds.left = br.left;
        if (br.top < bounds.top)
            bounds.top = br.top;
        if ((br.left + br.width) > bounds.width)
            bounds.width = (br.left + br.width);
        if ((br.top + br.height) > bounds.height)
            bounds.height = (br.top + br.height);

    }

    sf::FloatRect Entity::getSurfaceBounds(bool useGlobal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds = sf::FloatRect(inf, inf, -inf, -inf);
        for (const auto &it : this->components) {

            const sf::Transformable *t = it->t;
            if (!t)
                continue;
            if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t))
                t = as->getFrameBound(as->getFrameIndex());
            if (!t)
                continue;

            sf::FloatRect currentBounds;
            if (const BoundingShape *bs = dynamic_cast<const BoundingShape *>(t)) {
                if (useGlobal)
                    currentBounds = bs->getGlobalBounds();
                else
                    currentBounds = bs->getLocalBounds();
            }
            else if (const sf::Sprite *s = dynamic_cast<const sf::Sprite *>(t)) {
                if (useGlobal)
                    currentBounds = s->getGlobalBounds();
                else
                    currentBounds = s->getLocalBounds();
            }
            else if (const sf::Shape *sh = dynamic_cast<const sf::Shape *>(t)) {
                if (useGlobal)
                    currentBounds = sh->getGlobalBounds();
                else
                    currentBounds = sh->getLocalBounds();
            }
            else if (const sf::Text *t = dynamic_cast<const sf::Text *>(t)) {
                if (useGlobal)
                    currentBounds = t->getGlobalBounds();
                else
                    currentBounds = t->getLocalBounds();
            }
            else
                continue;

            if (useGlobal) {

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

    sf::FloatRect Entity::getTextureBounds(bool useGlobal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (const auto &it : this->components) {

            sf::FloatRect currentBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(it->d)) {
                if (useGlobal)
                    currentBounds = s->getGlobalBounds();
                else
                    currentBounds = s->getLocalBounds();
            }
            else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(it->d)) {
                if (useGlobal)
                    currentBounds = sh->getGlobalBounds();
                else
                    currentBounds = sh->getLocalBounds();
            }
            else if (sf::Text *t = dynamic_cast<sf::Text *>(it->d)) {
                if (useGlobal)
                    currentBounds = t->getGlobalBounds();
                else
                    currentBounds = t->getLocalBounds();
            }
            else if (sf::VertexArray *va = dynamic_cast<sf::VertexArray *>(it->d))
                currentBounds = va->getBounds();
            else
                continue;

            if (useGlobal) {

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

    std::vector<Component *>::size_type Entity::addDrawable(sf::Drawable &newDrawable, bool makeTransformable) {

        sf::Transformable *t = NULL;
        if (makeTransformable && (t = dynamic_cast<sf::Transformable *>(&newDrawable)))
            return this->addComponent(newDrawable, *t);

        Component *c = new Component();
        c->d = &newDrawable;
        c->t = t;
        this->components.push_back(c);
        return (this->getNumOfComponents() - 1);

    }

    std::vector<Component *>::size_type Entity::addTransformable(sf::Transformable &newTransformable, bool makeDrawable) {

        sf::Drawable *d = NULL;
        if (makeDrawable && (d = dynamic_cast<sf::Drawable *>(&newTransformable)))
            return this->addComponent(*d, newTransformable);

        if (dynamic_cast<Entity *>(&newTransformable))
            throw std::invalid_argument("Component\'s sf::Transfromable cannot be an Entity");
        Component *c = new Component();
        c->d = d;
        c->t = &newTransformable;
        this->components.push_back(c);
        return (this->getNumOfComponents() - 1);

    }

    std::vector<Component *>::size_type Entity::addComponent(sf::Drawable &newDrawable, sf::Transformable &newTransformable) {

        if (dynamic_cast<Entity *>(&newTransformable))
            throw std::invalid_argument("Component\'s sf::Transfromable cannot be an Entity");

        this->components.push_back(new Component(newDrawable, newTransformable));
        return (this->getNumOfComponents() - 1);

    }

    std::pair<sf::Drawable *, sf::Transformable *> Entity::removeComponent(uint32_t idx) {

        if (idx >= this->getNumOfComponents())
            return std::pair<sf::Drawable *, sf::Transformable *>(NULL, NULL);

        Component *r = this->components[idx];
        sf::Drawable *d = r->d;
        sf::Transformable *t = r->t;
        this->components.erase(this->components.begin() + idx);
        delete r;
        r = NULL;

        return std::pair<sf::Drawable *, sf::Transformable *>(d, t);

    }

    std::vector<Entity *>::size_type Entity::addPossession(Entity &newPossession) {

       const Entity *currentAncestor = this;
       if (newPossession.owner != NULL)
           return (this->getNumOfComponents() - 1);
       while (currentAncestor != NULL) {

           if (dynamic_cast<const void *>(currentAncestor) == dynamic_cast<void *>(&newPossession))
               return (this->getNumOfComponents() - 1);

           currentAncestor = currentAncestor->getOwner();

       }

       newPossession.owner = this;
       this->possessions.push_back(&newPossession);

       return (this->getNumOfComponents() - 1);

    }

    Entity *Entity::removePossession(uint32_t idx) {

        if (idx >= this->getNumOfPossessions())
            return NULL;

        Entity *r = this->possessions[idx];
        this->possessions.erase(this->possessions.begin() + idx);
        r->owner = NULL;

        return r;

    }

    int Entity::removePossession(Entity &removePossession) {

        uint32_t i;
        for (i = 0; i < this->getNumOfPossessions(); ++i) {

            if (dynamic_cast<void *>(this->possessions[i]) == dynamic_cast<void *>(&removePossession)) {

                this->possessions.erase(this->possessions.begin() + i);
                removePossession.owner = NULL;
                break;

            }

        }

        if (i < this->getNumOfPossessions())
            return i;

        return -1;

    }

}
