#include"BoundedSprite.hpp"

namespace sg {

    BoundedSprite::BoundedSprite() :
    sf::Sprite(),
    surface(NULL) {}

    BoundedSprite::BoundedSprite(BoundingShape &bs) :
    sf::Sprite(),
    surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(BoundingShape &bs, const sf::Texture &t) :
    sf::Sprite(t),
    surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(BoundingShape &bs, const sf::Texture &t, const sf::IntRect &rect) :
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

    void BoundedSprite::setSurface(BoundingShape &bs) {

        this->surface = &bs;

    }

    void BoundedSprite::setOrigin(float x, float y) {

        sf::Sprite::setOrigin(x, y);
        this->surface->setOrigin(sf::Vector2f(x, y));

    }

    void BoundedSprite::setOrigin(const sf::Vector2f &origin) {

        sf::Sprite::setOrigin(origin);
        this->surface->setOrigin(origin);

    }


    void BoundedSprite::setPosition(float x, float y) {

        sf::Sprite::setPosition(x, y);
        this->surface->setPosition(sf::Vector2f(x, y));

    }

    void BoundedSprite::setPosition(const sf::Vector2f &position) {

        sf::Sprite::setPosition(position);
        this->surface->setPosition(position);

    }

    void BoundedSprite::move(float offsetX, float offsetY) {

        sf::Sprite::move(offsetX, offsetY);
        this->surface->move(sf::Vector2f(offsetX, offsetY));

    }

    void BoundedSprite::move(const sf::Vector2f &offset) {

        sf::Sprite::move(offset);
        this->surface->move(offset);

    }

    void BoundedSprite::setRotation(float angle) {

        sf::Sprite::setRotation(angle);
        this->surface->setRotation(angle);

    }

    void BoundedSprite::rotate(float angle) {

        sf::Sprite::rotate(angle);
        this->surface->rotate(angle);

    }

    void BoundedSprite::setScale(float factorX, float factorY) {

        sf::Sprite::setScale(factorX, factorY);
        this->surface->setScale(sf::Vector2f(factorX, factorY));

    }

    void BoundedSprite::setScale(const sf::Vector2f &factor) {

        sf::Sprite::setScale(factor);
        this->surface->setScale(factor);

    }

    void BoundedSprite::scale(float factorX, float factorY) {

        sf::Sprite::scale(factorX, factorY);
        this->surface->scale(sf::Vector2f(factorX, factorY));

    }

    void BoundedSprite::scale(const sf::Vector2f &factor) {

        sf::Sprite::scale(factor);
        this->surface->scale(factor);

    }

}
