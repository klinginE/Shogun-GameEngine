#pragma once

//C++ includes
#include <vector>
#include <stdint.h>

//SFML includes
#include <SFML/Graphics.hpp>

namespace sg {

    class BoundingShape : public sf::Transformable {

        private:
            //Private member variables
            std::vector<sf::Shape *> shapes;
            //Private member functions
            sf::FloatRect getBounds(bool) const;
            const sf::ConvexShape approximateCircle(const sf::CircleShape &, const sf::Transformable &) const;
            sf::Vector2f calculateUnitNormal(const sf::Shape &, uint32_t, const sf::Transformable &) const;
            float projectPoint(const sf::Shape &, const sf::Vector2f &, uint32_t, const sf::Transformable &) const;
            bool collides_ptp(const sf::Shape &, const sf::Shape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &) const;
            bool collides_ctp(const sf::Shape &, const sf::Shape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &) const;
            bool collides_ctc(const sf::Shape &, const sf::Shape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &) const;

        public:
            //Public member functions
            ~BoundingShape();
            std::vector<sf::Shape *>::size_type getNumOfShapes() const;
            const sf::Shape *getShape(uint32_t) const;
            std::vector<sf::Shape *>::size_type addShape(sf::Shape &);
            const sf::Shape *removeShape(uint32_t);
            void setOrigin(float, float);
            void setOrigin(const sf::Vector2f &);
            void setPosition(float, float);
            void setPosition(const sf::Vector2f &);
            void move(float, float);
            void move(const sf::Vector2f &);
            void setRotation(float);
            void rotate(float);
            void setScale(const sf::Vector2f &);
            void setScale(float, float);
            void scale(const sf::Vector2f &);
            void scale(float, float);
            sf::FloatRect getLocalBounds() const;
            sf::FloatRect getGlobalBounds() const;
            bool collides(const BoundingShape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &) const;

    };

}
