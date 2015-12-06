#include"BundedSprite.hpp"

namespace sg {

    BoundedSprite::BoundedSprite() : sf::Sprite() {

        this->surface = NULL;

    }

    BoundedSprite::BoundedSprite(BoundingShape &bs) : sf::Sprite() {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(BoundingShape &bs, const sf::Texture &t) : sf::Sprite(t) {

        this->setSurface(bs);

    }

    BoundedSprite::BoundedSprite(BoundingShape &bs, const sf::Texture &t, const sf::IntRect &rect) : sf::Sprite(t, rect) {

        this->setSurface(bs);

    }

    BoundedSprite::~BoundedSprite() {

        this->surface = NULL;

    }

    const BoundedSprite::BoundingShape *getSurface() const {

        return surface;

    }

    void BoundedSprite::setSurface(BoundingShape &bs) {

        this->surface = &bs;

    }

}
