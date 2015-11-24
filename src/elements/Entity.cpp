#include"Entity.cpp"

namespace sg {

    Enity::Enity(sf::Vector2f startPos, setCollidable) {

        this->pos.x = startPos.x;
        this->pos.y = startPos.y;
        this->isCollidable = setCollidable;

    }

    Enity::~Enity() {

        this->pos.x = 0.0f;
        this->pos.y = 0.0f;
        this->setCollidable = false;
        sprites.clear();

    }

}
