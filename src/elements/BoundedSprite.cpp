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

}
