#pragma once

//C++ includes
#include<vector>
#include<stdint.h>

//SFML includes
#include<SFML/Graphics.hpp>

namespace sg {

    class BoundingShape {

        private:
            //Private member variables
            std::vector<sf::Shape *> shapes;
            //Private member functions
            sf::FloatRect getShapeBounds(bool) const;
            sf::Vector2f calculateUnitNormal(const sf::Shape &, uint32_t) const;
            float projectPoint(const sf::Shape &, const sf::Vector2f &, uint32_t) const;
            bool collides_ptp(const sf::Shape &, const sf::Shape &, sf::Vector2f &) const;
            bool collides_ctp(const sf::Shape &, const sf::Shape &, sf::Vector2f &) const;
            bool collides_ctc(const sf::Shape &, const sf::Shape &, sf::Vector2f &) const;

        public:
            //Public member functions
            BoundingShape();
            ~BoundingShape();
            std::vector<sf::Shape *>::size_type getNumOfShapes() const;
            const sf::Shape *getShape(uint32_t) const;
            std::vector<sf::Shape *>::size_type addShape(sf::Shape &);
            const sf::Shape *removeShape(uint32_t);
            void setPos(const sf::Vector2f &);
            void move(const sf::Vector2f &);
            sf::FloatRect getLocalShapeBounds() const;
            sf::FloatRect getGlobalShapeBounds() const;
            bool collides(const BoundingShape &, sf::Vector2f &) const;

    };

}
