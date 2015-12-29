#include"BoundedSprite.hpp"

namespace sg {

    BoundedSprite::BoundedSprite() :
    sf::Sprite(),
    surface(NULL)
    {

        this->surface = NULL;

    }

    BoundedSprite::BoundedSprite(const BoundingShape &bs) :
    sf::Sprite(),
    surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(const BoundingShape &bs, const sf::Texture &t) :
    sf::Sprite(t),
    surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(const BoundingShape &bs, const sf::Texture &t, const sf::IntRect &rect) :
    sf::Sprite(t, rect),
    surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::~BoundedSprite() {

        this->surface = NULL;

    }

    const BoundingShape *BoundedSprite::getSurface() const {

        return surface;

    }

    void BoundedSprite::setSurface(const BoundingShape &bs) {

        this->surface = &bs;

    }

    void BoundedSprite::setPosition(float x, float y) {

        sf::Sprite::setPosition(x, y);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setPosition(x, y);

    }

    void BoundedSprite::setPosition(const sf::Vector2f &position) {

        sf::Sprite::setPosition(position);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setPosition(position);

    }

    void BoundedSprite::move(float offsetX, float offsetY) {

        sf::Sprite::move(offsetX, offsetY);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->move(offsetX, offsetY);

    }

    void BoundedSprite::move(const sf::Vector2f &offset) {

        sf::Sprite::move(offset);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->move(offset);

    }

    void BoundedSprite::setOrigin(float x, float y) {

        sf::Sprite::setOrigin(x, y);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setOrigin(x, y);

    }

    void BoundedSprite::setOrigin(const sf::Vector2f &origin) {

        sf::Sprite::setOrigin(origin);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setOrigin(origin);

    }

    void BoundedSprite::setRotation(float angle) {

        sf::Sprite::setRotation(angle);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setRotation(angle);

    }

    void BoundedSprite::rotate(float angle) {

        sf::Sprite::rotate(angle);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->rotate(angle);

    }

    void BoundedSprite::setScale(float factorX, float factorY) {

        sf::Sprite::setScale(factorX, factorY);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setScale(factorX, factorY);

    }

    void BoundedSprite::scale(float factorX, float factorY) {

        sf::Sprite::scale(factorX, factorY);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->scale(factorX, factorY);

    }

    void BoundedSprite::setScale(const sf::Vector2f &factor) {

        sf::Sprite::setScale(factor);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->setScale(factor);

    }

    void BoundedSprite::scale(const sf::Vector2f &factor) {

        sf::Sprite::scale(factor);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++)
            //This const cast is dangerous as it could have undefined behavior
            (const_cast<sf::Shape *>(this->surface->getShape(i)))->scale(factor);

    }

}
