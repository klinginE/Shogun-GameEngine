#include"BoundedSprite.hpp"

namespace sg {

    BoundedSprite::BoundedSprite() :
    sf::Sprite(),
    this->surface(NULL)
    {

        this->surface = NULL;

    }

    BoundedSprite::BoundedSprite(const BoundingShape &bs) :
    sf::Sprite(),
    this->surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(const BoundingShape &bs, const sf::Texture &t) :
    sf::Sprite(t),
    this->surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(const BoundingShape &bs, const sf::Texture &t, const sf::IntRect &rect) :
    sf::Sprite(t, rect),
    this->surface(NULL)
    {

        this->setSurface(bs);

    }

    BoundedSprite::~BoundedSprite() {

        this->surface = NULL;

    }

    const BoundedSprite::BoundingShape *getSurface() const {

        return surface;

    }

    void BoundedSprite::setSurface(const BoundingShape &bs) {

        this->surface = &bs;

    }

}
