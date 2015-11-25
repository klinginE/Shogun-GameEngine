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

    bool Entity::collides(const sg::Entity &e) {

        if (!this->isCollidable)
            return false;

        //TODO: Add code that checks for collision with e.
        //this->handleCollision(...);
        return false;

    }

    bool Entity::getIsCollidable() {

        return this->isCollidable;

    }

    void Entity::setIsCollidable(bool flag) {

        this->isCollidable = flag;

    }

    std::vector<sf::Sprite *>::size_type Entity::getNumOfSprites() {

        return this->sprites.size();

    }

    const sf::Sprite *Entity::getSprite(uint32_t idx) {

        if (idx >= this->sprites.size() || idx < 0)
            return NULL;
        return this->sprites[idx];

    }

    void Entity::move(const sf::Vector2f &v) {

        this->pos.x = v.x;
        this->pos.y = v.y;

    }

    void Entity::moveSprite(uint32_t idx, const sf::Vector2f &v) {

        if (idx >= this->sprites.size() || idx < 0)
            return;
        this->sprites[idx]->setPosition(v);

    }

    void Entity::translate(const sf::Vector2f &v) {

        this->pos.x += v.x;
        this->pos.y += v.y;

    }

    void Entity::translateSprite(uint32_t idx, const sf::Vector2f &v) {

        if (idx >= this->sprites.size() || idx < 0)
            return;
        this->sprites[idx]->move(v);

    }

    void Entity::rotate(float angl, bool useDeg) {

        for (uint32_t i = 0; 0 < this->sprites.size(); i++)
            this->rotateSprite(i, angl, useDeg);

    }

    void Entity::rotateSprite(uint32_t idx, float angl, bool useDeg) {

        if (idx >= this->sprites.size() || idx < 0)
            return;
        if (!useDeg)
            angl *= (180.0f / M_PI);//If angl is not degs then make it degs
        this->sprites[idx]->rotate(angl);

    }

    void Entity::scale(const sf::Vector2f &s) {

        for (uint32_t i = 0; 0 < this->sprites.size(); i++)
            this->scaleSprite(i, s);

    }

    void Entity::scaleSprite(uint32_t idx, const sf::Vector2f &s) {

        if (idx >= this->sprites.size() || idx < 0)
            return;
        this->sprites[idx]->scale(s); 

    }

    const sf::Vector2f &Entity::getPos() {

        return this->pos;

    }

    const sf::Vector2f &Entity::getPosSprite(uint32_t idx) {

        if (idx >= this->sprites.size() || idx < 0) {

            //TODO: come up with a better way to return
            sf::Vector2f rPos;
            return rPos;

        }
        return this->sprites[idx]->getPosition();

    }

    std::vector<sf::Sprite *>::size_type Entity::addSprite(sf::Sprite *newSprite) {

        this->sprites.push_back(newSprite);
        return (this->sprites.size() - 1);

    }

    sf::Sprite *Entity::removeSprite(uint32_t idx) {

        if (idx >= this->sprites.size() || idx < 0)
            return NULL;
        sf::Sprite *r = this->sprites[idx];
        this->sprites.erase(sprites.begin() + idx);
        return r;

    }

    sf::Sprite *Entity::removeSprite(sf::Sprite *s) {

        std::vector<sf::Sprite *>::iterator it = this->sprites.begin();
        while (it != this->sprites.end()) {

            if ((*it) == s) {

                this->sprites.erase(it);
                return (*it);

            }
            ++it;

        }

        return NULL;

    }

    void Entity::draw() {

        //TODO: Add code to get render window and loop through sprites and draw
        //      them.

    }

}
