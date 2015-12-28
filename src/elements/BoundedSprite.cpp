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

    void BoundedSprite::setRotation(float angle) {

        sf::Sprite::setRotation(angle);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++) {

            //This const cast is dangerous as it could have undefined behavior
            sf::Shape *curShape = const_cast<sf::Shape *>(this->surface->getShape(i));
            const sf::Vector2f &temp = curShape->getOrigin();
            curShape->setOrigin(this->getOrigin());
            curShape->setRotation(angle);
            curShape->setOrigin(temp);

        }

    }

    void BoundedSprite::rotate(float angle) {

        sf::Sprite::rotate(angle);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++) {

            //This const cast is dangerous as it could have undefined behavior
            sf::Shape *curShape = const_cast<sf::Shape *>(this->surface->getShape(i));
            const sf::Vector2f temp = curShape->getOrigin();
            curShape->setOrigin(this->getOrigin());
            curShape->rotate(angle);
            curShape->setOrigin(temp);

        }

    }

    void BoundedSprite::setScale(float factorX, float factorY) {

        sf::Sprite::setScale(factorX, factorY);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++) {

            //This const cast is dangerous as it could have undefined behavior
            sf::Shape *curShape = const_cast<sf::Shape *>(this->surface->getShape(i));
            const sf::Vector2f temp = curShape->getOrigin();
            curShape->setOrigin(this->getOrigin());
            curShape->setScale(factorX, factorY);
            curShape->setOrigin(temp);

        }

    }

    void BoundedSprite::scale(float factorX, float factorY) {

        sf::Sprite::scale(factorX, factorY);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++) {

            //This const cast is dangerous as it could have undefined behavior
            sf::Shape *curShape = const_cast<sf::Shape *>(this->surface->getShape(i));
            const sf::Vector2f temp = curShape->getOrigin();
            curShape->setOrigin(this->getOrigin());
            curShape->scale(factorX, factorY);
            curShape->setOrigin(temp);

        }

    }

    void BoundedSprite::setScale(const sf::Vector2f &factor) {

        sf::Sprite::setScale(factor);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++) {

            //This const cast is dangerous as it could have undefined behavior
            sf::Shape *curShape = const_cast<sf::Shape *>(this->surface->getShape(i));
            const sf::Vector2f temp = curShape->getOrigin();
            curShape->setOrigin(this->getOrigin());
            curShape->setScale(factor);
            curShape->setOrigin(temp);

        }

    }

    void BoundedSprite::scale(const sf::Vector2f &factor) {

        sf::Sprite::scale(factor);
        for (uint32_t i = 0; i <= this->surface->getNumOfShapes(); i++) {

            //This const cast is dangerous as it could have undefined behavior
            sf::Shape *curShape = const_cast<sf::Shape *>(this->surface->getShape(i));
            const sf::Vector2f temp = curShape->getOrigin();
            curShape->setOrigin(this->getOrigin());
            curShape->scale(factor);
            curShape->setOrigin(temp);

        }

    }

}
