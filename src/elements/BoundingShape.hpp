#pragma once

//C++ includes
#include<vector>
#include<stdint.h>

//SFML includes
#include<SFML/Graphics.hpp>

namespace sg {

    class BoundingShape {

        private:
            std::vector<const sf::Shape *> shapes;
            sf::FloatRect getShapeBounds(bool) const;

        public:
            BoundingShape();
            ~BoundingShape();
            std::vector<const sf::Shape *>::size_type getNumOfShapes() const;
            const sf::Shape *getShape(uint32_t) const;
            std::vector<const sf::Shape *>::size_type addShape(const sf::Shape &);
            const sf::Shape *removeShape(uint32_t);
            sf::FloatRect getLocalShapeBounds() const;
            sf::FloatRect getGlobalShapeBounds() const;

    };

}
