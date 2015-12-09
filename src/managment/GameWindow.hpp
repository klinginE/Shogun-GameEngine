#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameWorld.hpp"

namespace sg {
    
    class GameWindow {
    
        sf::Vector2f positionInScreen;
        sf::Vector2f sizeInScreen;
        sf::Vector2f positionInWorld;
        sf::Vector2f sizeInWorld;
        float rotationInWorld;
        GameWorld *world;
        sf::View view;
    
        public:
            GameWindow(GameWorld *world);
            GameWindow(GameWorld *world,
                       sf::Vector2f positionInScreen,
                       sf::Vector2f sizeInScreen,
                       sf::Vector2f positionInWorld,
                       sf::Vector2f sizeInWorld,
                       float rotationInWorld);
            GameWindow(GameWorld *world,
                       sf::Vector2f positionInScreen,
                       sf::Vector2f sizeInScreen,
                       sf::Vector2f positionInWorld,
                       sf::Vector2f sizeInWorld);
            GameWindow(GameWorld *world,
                       sf::Vector2f positionInWorld,
                       sf::Vector2f sizeInWorld,
                       float rotationInWorld);
            GameWindow(GameWorld *world,
                       sf::Vector2f positionInScreen,
                       sf::Vector2f sizeInScreen);
    
            void render();
    
            void setWorld(GameWorld *newWorld);
            GameWorld *getWorld();
    
            void setPosInScreen(sf::Vector2f positionInScreen);
            sf::Vector2f getPosInScreen();
    
            void setSizeInScreen(sf::Vector2f sizeInScreen);
            sf::Vector2f getSizeInScreen();
    
            void setPosInWorld(sf::Vector2f posInWorld);
            sf::Vector2f getPosInWorld();
    
            void setSizeInWorld(sf::Vector2f sizeInWorld);
            sf::Vector2f getSizeInWorld();
    
            void setRotInWorld(float rotationInWorld);
            float getRotInWorld();
    
        private:
            
            void updateView();
    
    };

}
