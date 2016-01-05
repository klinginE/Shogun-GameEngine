//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"Entity.hpp"

namespace sg {

    Entity::Entity() :
    sf::Transformable()
    {

        this->isCollidable = true;

    }

    Entity::Entity(bool setCollidable) :
    sf::Transformable()
    {

        this->isCollidable = setCollidable;

    }

    Entity::~Entity() {

        this->isCollidable = false;
        this->sprites.clear();

    }

    bool Entity::collides(sg::Entity &e) {

        if (!this->isCollidable || !e.getIsCollidable())
            return false;

        bool isCollides = false;
        std::vector<sf::Vector2f> collisionVectors;
        for (std::vector<sf::Drawable *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            for (uint32_t i = 0; i < e.getNumOfSprites(); i++) {

                sf::Drawable *sp0 = (*it);
                const sf::Drawable *sp1 = e.getSprite(i);
                const BoundingShape *s0 = NULL;
                const BoundingShape *s1 = NULL;
                if (AnimatedSprite *as = dynamic_cast<AnimatedSprite *>(sp0))
                    s0 = dynamic_cast<const BoundingShape *>(as->getFrameBound(as->getFrameIndex()));
                else if (BoundedSprite *bs = dynamic_cast<BoundedSprite *>(sp0))
                    s0 = dynamic_cast<const BoundingShape *>(bs->getSurface());
                if (const AnimatedSprite *as = dynamic_cast<const AnimatedSprite *>(sp1))
                    s1 = dynamic_cast<const BoundingShape *>(as->getFrameBound(as->getFrameIndex()));
                else if (const BoundedSprite *bs = dynamic_cast<const BoundedSprite *>(sp1))
                    s1 = dynamic_cast<const BoundingShape *>(bs->getSurface());

                sf::Vector2f v(0.0f, 0.0f);
                if (s0 != NULL && s1 != NULL && s0->collides((*s1), v, this->getTransform(), e.getTransform())) {

                    isCollides = true;
                    collisionVectors.push_back(v);

                }

            }

        this->handleCollision(e, collisionVectors);

        return isCollides;

    }

    bool Entity::getIsCollidable() const {

        return this->isCollidable;

    }

    void Entity::setIsCollidable(bool flag) {

        this->isCollidable = flag;

    }

    std::vector<sf::Drawable *>::size_type Entity::getNumOfSprites() const {

        return this->sprites.size();

    }

    const sf::Drawable *Entity::getSprite(uint32_t idx) const {

        if (idx >= this->getNumOfSprites())
            return NULL;
        return this->sprites[idx];

    }

    void Entity::setOriginSprite(uint32_t idx, const sf::Vector2f &origin) {

        if (idx >= this->getNumOfSprites())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->setOrigin(origin);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->setOrigin(origin);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->setOrigin(origin);

    }

    void Entity::setPositionSprite(uint32_t idx, const sf::Vector2f &position) {

        if (idx >= this->getNumOfSprites())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->setPosition(position);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->setPosition(position);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->setPosition(position);

    }

    void Entity::moveSprite(uint32_t idx, const sf::Vector2f &offset) {

        if (idx >= this->getNumOfSprites())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->move(offset);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->move(offset);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->move(offset);

    }

    void Entity::setRotationSprite(uint32_t idx, float angle, bool useDeg) {

        if (idx >= this->getNumOfSprites())
            return;
        if (!useDeg)
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->setRotation(angle);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->setRotation(angle);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->setRotation(angle);

    }

    void Entity::rotateSprite(uint32_t idx, float angle, bool useDeg) {

        if (idx >= this->getNumOfSprites())
            return;
        if (!useDeg)
            angle *= (180.0f / M_PI);//If angl is not degs then make it degs

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->rotate(angle);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->rotate(angle);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->rotate(angle);

    }

    void Entity::setScaleSprite(uint32_t idx, const sf::Vector2f &factor) {

        if (idx >= this->getNumOfSprites())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->setScale(factor);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->setScale(factor);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->setScale(factor);

    }

    void Entity::scaleSprite(uint32_t idx, const sf::Vector2f &factor) {

        if (idx >= this->getNumOfSprites())
            return;

        if (sf::Sprite *s = dynamic_cast<sf::Sprite *>(this->sprites[idx]))
            s->scale(factor);
        else if (sf::Shape *sh = dynamic_cast<sf::Shape *>(this->sprites[idx]))
            sh->scale(factor);
        else if (sf::Text *t = dynamic_cast<sf::Text *>(this->sprites[idx]))
            t->scale(factor);

    }

    void Entity::expandSurfaceBounds(sf::FloatRect &bounds, sf::FloatRect br) {

        if (br.left < bounds.left)
            bounds.left = br.left;
        if (br.top < bounds.top)
            bounds.top = br.top;
        if ((br.left + br.width) > bounds.width)
            bounds.width = (br.left + br.width);
        if ((br.top + br.height) > bounds.height)
            bounds.height = (br.top + br.height);

    }

    sf::FloatRect Entity::getSurfaceBounds(bool useGlobal) {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<sf::Drawable *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {

            sf::FloatRect currentBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (AnimatedSprite *as = dynamic_cast<AnimatedSprite *>((*it))) {
                if (useGlobal)
                    currentBounds = as->getFrameBound(as->getFrameIndex())->getGlobalShapeBounds();
                else
                    currentBounds = as->getFrameBound(as->getFrameIndex())->getLocalShapeBounds();
            }
            else if (BoundedSprite *bs = dynamic_cast<BoundedSprite *>((*it))) {
                if (useGlobal)
                    currentBounds = bs->getSurface()->getGlobalShapeBounds();
                else
                    currentBounds = bs->getSurface()->getLocalShapeBounds();
            }
            else
                continue;

            if (useGlobal) {

                sf::ConvexShape transBounds(4);
                transBounds.setPoint(0, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left, currentBounds.top)));
                transBounds.setPoint(1, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left + currentBounds.width, currentBounds.top)));
                transBounds.setPoint(2, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left + currentBounds.width, currentBounds.top + currentBounds.height)));
                transBounds.setPoint(3, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left, currentBounds.top + currentBounds.height)));
                currentBounds = transBounds.getGlobalBounds();

            }
            this->expandSurfaceBounds(bounds, currentBounds);

        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;

    }

    sf::FloatRect Entity::getTextureBounds(bool useGlobal) {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<sf::Drawable *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {

            sf::FloatRect currentBounds(0.0f, 0.0f, 0.0f, 0.0f);
            if (sf::Sprite *s = dynamic_cast<sf::Sprite *>((*it))) {
                if (useGlobal)
                    currentBounds = s->getGlobalBounds();
                else
                    currentBounds = s->getLocalBounds();
            }
            else if (sf::Shape *sh = dynamic_cast<sf::Shape *>((*it))) {
                if (useGlobal)
                    currentBounds = sh->getGlobalBounds();
                else
                    currentBounds = sh->getLocalBounds();
            }
            else if (sf::Text *t = dynamic_cast<sf::Text *>((*it))) {
                if (useGlobal)
                    currentBounds = t->getGlobalBounds();
                else
                    currentBounds = t->getLocalBounds();
            }
            else if (sf::VertexArray *va = dynamic_cast<sf::VertexArray *>((*it)))
                currentBounds = va->getBounds();
            else
                continue;

            if (useGlobal) {

                sf::ConvexShape transBounds(4);
                transBounds.setPoint(0, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left, currentBounds.top)));
                transBounds.setPoint(1, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left + currentBounds.width, currentBounds.top)));
                transBounds.setPoint(2, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left + currentBounds.width, currentBounds.top + currentBounds.height)));
                transBounds.setPoint(3, this->getTransform().transformPoint(sf::Vector2f(currentBounds.left, currentBounds.top + currentBounds.height)));
                currentBounds = transBounds.getGlobalBounds();

            }
            this->expandSurfaceBounds(bounds, currentBounds);

        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;

    }

    std::vector<sf::Drawable *>::size_type Entity::addSprite(sf::Drawable &newSprite) {

        this->sprites.push_back(&newSprite);
        return (this->getNumOfSprites() - 1);

    }

    sf::Drawable *Entity::removeSprite(uint32_t idx) {

        if (idx >= this->getNumOfSprites())
            return NULL;
        sf::Drawable *r = this->sprites[idx];
        this->sprites.erase(this->sprites.begin() + idx);
        return r;

    }

}
