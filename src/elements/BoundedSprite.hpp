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
            const BoundingShape *surface;
            sf::FloatRect getShapeBounds(bool);

        public:
            BoundedSprite();
            BoundedSprite(const BoundingShape &);
            BoundedSprite(const BoundingShape &, const sf::Texture &);
            BoundedSprite(const BoundingShape &, const sf::Texture &, const sf::IntRect &);
            ~BoundedSprite();
            const BoundingShape *getSurface() const;
            void setSurface(const BoundingShape &);
            void setRotation(float angle);
            void rotate(float angle);
            void setScale(float, float);
            void scale(float, float);
            void setScale(const sf::Vector2f &);
            void scale(const sf::Vector2f &);

    };

}
