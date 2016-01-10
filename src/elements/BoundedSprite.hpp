#pragma once

//C++ includes
#include<vector>

//SFML includes
#include<SFML/Graphics.hpp>

//Shogun includes
#include"BoundingShape.hpp"

namespace sg {

    class BoundedSprite : public sf::Sprite {

        private:
            BoundingShape *surface;

        public:
            BoundedSprite();
            BoundedSprite(BoundingShape &);
            BoundedSprite(BoundingShape &, const sf::Texture &);
            BoundedSprite(BoundingShape &, const sf::Texture &, const sf::IntRect &);
            ~BoundedSprite();
            const BoundingShape *getSurface() const;
            void setSurface(BoundingShape &);
            void setOrigin(float, float);
            void setOrigin(const sf::Vector2f &);
            void setPosition(float, float);
            void setPosition(const sf::Vector2f &);
            void move(float, float);
            void move(const sf::Vector2f &);
            void setRotation(float angle);
            void rotate(float angle);
            void setScale(float, float);
            void setScale(const sf::Vector2f &);
            void scale(float, float);
            void scale(const sf::Vector2f &);

    };

}
