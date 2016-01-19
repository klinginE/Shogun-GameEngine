//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"Entity.hpp"

namespace sg {

    Entity::Entity() :
    sf::Transformable()
    {

        //this->owner = NULL;
        this->isCollidable = true;
        this->deletion = false;

    }

    Entity::Entity(bool setCollidable) :
    sf::Transformable()
    {

        //this->owner = NULL;
        this->isCollidable = setCollidable;
        this->deletion = false;

    }

    Entity::~Entity() {

        //this->owner = NULL;
        this->isCollidable = false;
        this->deletion = false;
        this->components.clear();
        //this->possessions.clear();

    }

    bool Entity::collides(sg::Entity &e) {

        if (!this->isCollidable || !e.getIsCollidable())
            return false;

        bool isCollides = false;
        std::vector<sf::Vector2f> collisionVectors;
        for (std::vector<Component *>::iterator it = this->components.begin(); it != this->components.end(); ++it)
            for (uint32_t i = 0; i < e.getNumOfComponents(); i++) {

                const sf::Transformable *t0 = (*it)->t;
                if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t0))
                    t0 = as->getFrameBound(as->getFrameIndex());

                const sf::Transformable *t1 = e.getComponent(i)->t;
                if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t1))
                    t1 = as->getFrameBound(as->getFrameIndex());

                sf::RectangleShape tempRs0;
                BoundingShape tempShape0;
                const BoundingShape *s0 = NULL;
                if (const BoundingShape *bs = dynamic_cast<const BoundingShape *>(t0))
                    s0 = bs;
                else {

                    sf::FloatRect t0Bounds;
                    if (const sf::Sprite *s = dynamic_cast<const sf::Sprite *>(t0))
                        t0Bounds = s->getLocalBounds();
                    else if (const sf::Shape *sh = dynamic_cast<const sf::Shape *>(t0))
                        t0Bounds = sh->getLocalBounds();
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
                const BoundingShape *s1 = NULL;
                if (const BoundingShape *bs = dynamic_cast<const BoundingShape *>(t1))
                    s1 = bs;
                else {

                    sf::FloatRect t1Bounds;
                    if (const sf::Sprite *s = dynamic_cast<const sf::Sprite *>(t1))
                        t1Bounds = s->getLocalBounds();
                    else if (const sf::Shape *sh = dynamic_cast<const sf::Shape *>(t1))
                        t1Bounds = sh->getLocalBounds();
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

                sf::Vector2f v(0.0f, 0.0f);
                if (s0 != NULL && s1 != NULL && s0->collides((*s1), v, dynamic_cast<const sf::Transformable &>((*this)), dynamic_cast<const sf::Transformable &>(e))) {

                    isCollides = true;
                    collisionVectors.push_back(v);

                }

            }

        if (isCollides)
            this->handleCollision(e, collisionVectors);

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

    const Component *Entity::getComponent(uint32_t idx) const {

        if (idx >= this->getNumOfComponents())
            return NULL;
        return this->components[idx];

    }

//    std::vector<Entity *>::size_type Entity::getNumOfPossessions() const {
//
//        return this->possessions.size();
//
//    }
//
//    const Entity *Entity::getPossession(uint32_t idx) const {
//
//        if (idx >= this->getNumOfPossessions())
//            return NULL;
//        return this->possessions[idx];
//
//    }
//
//    const Entity *Entity::getOwner() const {
//
//        return this->owner;
//
//    }

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
        for (std::vector<Component *>::const_iterator it = this->components.begin(); it != this->components.end(); ++it) {

            const sf::Transformable *t = (*it)->t;
            if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(t))
                t = as->getFrameBound(as->getFrameIndex());

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

            if (useGlobal)
                currentBounds = this->getTransform().transformRect(currentBounds);
            this->expandSurfaceBounds(bounds, currentBounds);

        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;

    }

    sf::FloatRect Entity::getTextureBounds(bool useGlobal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<Component *>::const_iterator it = this->components.begin(); it != this->components.end(); ++it) {

            sf::FloatRect currentBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (sf::Sprite *s = dynamic_cast<sf::Sprite *>((*it)->d)) {
                if (useGlobal)
                    currentBounds = s->getGlobalBounds();
                else
                    currentBounds = s->getLocalBounds();
            }
            else if (sf::Shape *sh = dynamic_cast<sf::Shape *>((*it)->d)) {
                if (useGlobal)
                    currentBounds = sh->getGlobalBounds();
                else
                    currentBounds = sh->getLocalBounds();
            }
            else if (sf::Text *t = dynamic_cast<sf::Text *>((*it)->d)) {
                if (useGlobal)
                    currentBounds = t->getGlobalBounds();
                else
                    currentBounds = t->getLocalBounds();
            }
            else if (sf::VertexArray *va = dynamic_cast<sf::VertexArray *>((*it)->d))
                currentBounds = va->getBounds();
            else
                continue;

            if (useGlobal)
                currentBounds = this->getTransform().transformRect(currentBounds);
            this->expandSurfaceBounds(bounds, currentBounds);

        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;

    }

    std::vector<Component *>::size_type Entity::addComponent(Component &newComponent) {

        if (dynamic_cast<Entity *>(newComponent.t))
            throw std::invalid_argument("Component\'s sf::Transfromable cannot be an Entity");

        if (newComponent.d != NULL || newComponent.t != NULL)
            this->components.push_back(&newComponent);

        return (this->getNumOfComponents() - 1);

    }

    Component *Entity::removeComponent(uint32_t idx) {

        if (idx >= this->getNumOfComponents())
            return NULL;

        Component *r = this->components[idx];
        this->components.erase(this->components.begin() + idx);

        return r;

    }

//    std::vector<Entity *>::size_type Entity::addPossession(Entity &newPossession) {
//
//       const Entity *currentAncestor = this;
//       while (currentAncestor != NULL) {
//
//           if (currentAncestor == &newPossession)
//               return (this->getNumOfComponents() - 1);
//
//           currentAncestor = currentAncestor->getOwner();
//
//       }
//
//       newPossession.owner = this;
//       this->possessions.push_back(&newPossession);
//
//       return (this->getNumOfComponents() - 1);
//
//    }
//
//    Entity *Entity::removePossession(uint32_t idx) {
//
//        if (idx >= this->getNumOfPossessions())
//            return NULL;
//
//        Entity *r = this->possessions[idx];
//        this->possessions.erase(this->possessions.begin() + idx);
//        r.owner = NULL;
//
//        return r;
//
//    }

    void Entity::draw() {

        this->render();

    }

}
