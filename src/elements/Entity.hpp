#pragma once

//C++ includes
#include<iostream>
#include<vector>

//SFML includes
#include<SFML/Graphics>

namespace sg {

    class Entity {

        private:
            std::vector<sf::Sprite *> sprites();
            bool isCollidable;
            sf::Vector2f pos;//world coordinates

        public:
            Entity(sf::Vector2f, bool=true);
            ~Entity();
            bool collides(sg::Entity);// calls handleCollision
            virtual void handleCollision(std::string, sf::Vector2f, std::vector<sf::Vector2f>);
            bool getIsCollidable();
            void move(sf::Vector2f);
            void moveSprite(int, sf::Vector2f);
            void translate(sf::Vector2f);
            void translateSprite(int, sf::Vector2f);
            void rotate(float, bool=true);
            void rotateSprite(int, float, bool=true);
            sf::Vector2f getPos();
            sf::Vector2f getPosSprite(int);
            virtual void update(float);
            void draw();

    };

}
