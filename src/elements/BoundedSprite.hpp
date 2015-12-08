#pragma once

//C++ includes
#include<vector>

//SFML includes
#include<SFML/Graphics.hpp>

//Shogun includes
#include"BoundingShape.hpp"
//#include<SHOGUN/elements/BoundingShape.hpp>

namespace sg {

    class BoundedSprite : public sf::Sprite {

        private:
            const BoundingShape *surface;
        public:
            BoundedSprite();
            BoundedSprite(const BoundingShape &);
            BoundedSprite(const BoundingShape &, const sf::Texture &);
            BoundedSprite(const BoundingShape &, const sf::Texture &, const sf::IntRect &);
            ~BoundedSprite();
            const BoundingShape *getSurface() const;
            void setSurface(const BoundingShape &);

    };

}
