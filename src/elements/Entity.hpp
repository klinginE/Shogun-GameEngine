#pragma once

//C++ includes
#include<iostream>
#include<vector>
#include<math.h>
#include<stdint.h>

//SFML includes
#include<SFML/Graphics.hpp>

namespace sg {

    class Entity {

        protected:
            std::vector<sf::Sprite *> sprites;
            bool isCollidable;
            sf::Vector2f pos;//world coordinates

        public:
            Entity();
            Entity(const sf::Vector2f &, bool=true);
            ~Entity();
            bool collides(const sg::Entity &);// calls handleCollision
            /*virtual*/ void handleCollision(std::string, const sf::Vector2f &, const std::vector<sf::Vector2f> &) {};
            bool getIsCollidable();
            void setIsCollidable(bool);
            void move(const sf::Vector2f &);
            void moveSprite(uint32_t, const sf::Vector2f &);
            void translate(const sf::Vector2f &);
            void translateSprite(uint32_t, const sf::Vector2f &);
            void rotate(float, bool=true);
            void rotateSprite(uint32_t, float, bool=true);
            void scale(const sf::Vector2f &);
            void scaleSprite(uint32_t, const sf::Vector2f &);
            const sf::Vector2f &getPos();
            const sf::Vector2f &getPosSprite(uint32_t);
            std::vector<sf::Sprite *>::size_type addSprite(sf::Sprite *);
            sf::Sprite *removeSprite(uint32_t);
            sf::Sprite *removeSprite(sf::Sprite *);
            /*virtual*/ void update(float) /*= 0;*/ {}
            void draw();

    };

}
