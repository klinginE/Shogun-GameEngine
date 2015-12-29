//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"Entity.hpp"

namespace sg {

    Entity::Entity() {

        this->pos.x = 0.0f;
        this->pos.y = 0.0f;
        this->isCollidable = true;

    }

    Entity::Entity(const sf::Vector2f &startPos, bool setCollidable) {

        this->pos.x = startPos.x;
        this->pos.y = startPos.y;
        this->isCollidable = setCollidable;

    }

    Entity::~Entity() {

        this->pos.x = 0.0f;
        this->pos.y = 0.0f;
        this->isCollidable = false;
        this->sprites.clear();

    }

    bool Entity::collides(sg::Entity &e) {

        if (!this->isCollidable || !e.getIsCollidable())
            return false;

        bool isCollides = false;
        std::vector<sf::Vector2f> collisionVectors;
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            for (uint32_t i = 0; i < e.getNumOfSprites(); i++) {

                 sf::Sprite *sp0 = (*it);
                 const sf::Sprite *sp1 = e.getSprite(i);
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
                 if (s0 != NULL && s1 != NULL && s0->collides((*s1), v)) {

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

    std::vector<sf::Sprite *>::size_type Entity::getNumOfSprites() const {

        return this->sprites.size();

    }

    const sf::Sprite *Entity::getSprite(uint32_t idx) const {

        if (idx >= this->getNumOfSprites())
            return NULL;
        return this->sprites[idx];

    }

    void Entity::setPos(const sf::Vector2f &v) {

        this->pos.x = v.x;
        this->pos.y = v.y;
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            (*it)->setPosition(v);

    }

    /*void Entity::setPosSprite(uint32_t idx, const sf::Vector2f &v) {

        if (idx >= this->getNumOfSprites())
            return;
        this->sprites[idx]->setPosition(v);

    }*/

    void Entity::move(const sf::Vector2f &v) {

        this->pos.x += v.x;
        this->pos.y += v.y;
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            (*it)->move(v);

    }

    /*void Entity::moveSprite(uint32_t idx, const sf::Vector2f &v) {

        if (idx >= this->getNumOfSprites())
            return;
        this->sprites[idx]->move(v);

    }*/

    void Entity::setOrigin(const sf::Vector2f &origin) {

        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            (*it)->setOrigin(origin);

    }

    void Entity::rotate(float angl, bool useDeg) {

        for (uint32_t i = 0; 0 < this->getNumOfSprites(); i++)
            this->rotateSprite(i, angl, useDeg);

    }

    void Entity::rotateSprite(uint32_t idx, float angl, bool useDeg) {

        if (idx >= this->getNumOfSprites())
            return;
        if (!useDeg)
            angl *= (180.0f / M_PI);//If angl is not degs then make it degs
        this->sprites[idx]->rotate(angl);

    }

    void Entity::scale(const sf::Vector2f &s) {

        for (uint32_t i = 0; 0 < this->getNumOfSprites(); i++)
            this->scaleSprite(i, s);

    }

    void Entity::scaleSprite(uint32_t idx, const sf::Vector2f &s) {

        if (idx >= this->getNumOfSprites())
            return;
        this->sprites[idx]->scale(s); 

    }

    const sf::Vector2f &Entity::getPos() const {

        return this->pos;

    }

    const sf::Vector2f &Entity::getPosSprite(uint32_t idx) const {

        if (idx >= this->getNumOfSprites())
            throw std::out_of_range("getPosSprite(): Not a vaild sprite index.");
        return this->sprites[idx]->getPosition();

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
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            if (AnimatedSprite *as = dynamic_cast<AnimatedSprite *>((*it))) {
                if (useGlobal)
                    this->expandSurfaceBounds(bounds, as->getFrameBound(as->getFrameIndex())->getGlobalShapeBounds());
                else
                    this->expandSurfaceBounds(bounds, as->getFrameBound(as->getFrameIndex())->getLocalShapeBounds());
            }
            else if (BoundedSprite *bs = dynamic_cast<BoundedSprite *>((*it))) {
                if (useGlobal)
                    this->expandSurfaceBounds(bounds, bs->getSurface()->getGlobalShapeBounds());
                else
                    this->expandSurfaceBounds(bounds, bs->getSurface()->getLocalShapeBounds());
            }
            else {
                if (useGlobal)
                    this->expandSurfaceBounds(bounds, (*it)->getGlobalBounds());
                else
                    this->expandSurfaceBounds(bounds, (*it)->getLocalBounds());
            }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;
        bounds.left += this->pos.x;
        bounds.top += this->pos.y;

        return bounds;

    }

    sf::FloatRect Entity::getTextureBounds(bool useGlobal) {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
            if (useGlobal)
                this->expandSurfaceBounds(bounds, (*it)->getGlobalBounds());
            else
                this->expandSurfaceBounds(bounds, (*it)->getLocalBounds());

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;
        bounds.left += this->pos.x;
        bounds.top += this->pos.y;

        return bounds;

    }

    std::vector<sf::Sprite *>::size_type Entity::addSprite(sf::Sprite &newSprite) {

        this->sprites.push_back(&newSprite);
        return (this->getNumOfSprites() - 1);

    }

    sf::Sprite *Entity::removeSprite(uint32_t idx) {

        if (idx >= this->getNumOfSprites())
            return NULL;
        sf::Sprite *r = this->sprites[idx];
        this->sprites.erase(this->sprites.begin() + idx);
        return r;

    }

}
