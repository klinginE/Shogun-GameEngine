//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"Entity.hpp"
//TODO: uncomment code once GameLoop is ready.
//#include"../management/GameLoop.hpp"

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

    bool Entity::collides(const sg::Entity &e) {

        if (!this->isCollidable)
            return false;

        //TODO: Add code that checks for collision with e.
        //this->handleCollision(...);
        return false;

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

    void Entity::move(const sf::Vector2f &v) {

        this->pos.x = v.x;
        this->pos.y = v.y;

    }

    void Entity::moveSprite(uint32_t idx, const sf::Vector2f &v) {

        if (idx >= this->getNumOfSprites())
            return;
        this->sprites[idx]->setPosition(v);

    }

    void Entity::translate(const sf::Vector2f &v) {

        this->pos.x += v.x;
        this->pos.y += v.y;

    }

    void Entity::translateSprite(uint32_t idx, const sf::Vector2f &v) {

        if (idx >= this->getNumOfSprites())
            return;
        this->sprites[idx]->move(v);

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

    void Entity::expandTextureBounds(sf::FloatRect &bounds, sf::FloatRect br) {

        if (br.left < bounds.left)
            bounds.left = br.left;
        if (br.top < bounds.top)
            bounds.top = br.top;
        if ((br.left + br.width) > br.width)
            bounds.width = (br.left + br.width);
        if ((br.top + br.height) > br.height)
            bounds.height = (br.top + br.height);

    }

    const sf::FloatRect &Entity::getSurfaceBounds() {

        //TODO: add code to itterate through animated and bounded sprite for loops and call private expand functions
        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin() ; it != this->sprites.end(); ++it)
            if (AnimatedSprite *as = dynamic_cast<AnimatedSprite *>((*it))) {}
                /*for ()
                    this->expandSurfaceBounds(bounds, );*/
            else if (BoundedSprite *bs = dynamic_cast<BoundedSprite *>((*it))) {}
                /*for ()
                    this->expandSurfaceBounds(bounds, );*/
            else
                this->expandBounds(bounds, (*it)->getGlobalBounds());

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;
        bounds.left += this->pos.x;
        bounds.top += this->pos.y;

        return bounds;

    }

    sf::FloatRect Entity::getTextureBounds() {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin() ; it != this->sprites.end(); ++it)
            this->expandBounds(bounds, (*it)->getGlobalBounds());

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
