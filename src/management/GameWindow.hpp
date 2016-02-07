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
        const GameWorld *world;
        sf::View view;
    
        public:
            GameWindow();
            GameWindow(const GameWorld &world);
            GameWindow(const GameWorld &world,
                       sf::Vector2f positionInScreen,
                       sf::Vector2f sizeInScreen,
                       sf::Vector2f positionInWorld,
                       sf::Vector2f sizeInWorld,
                       float rotationInWorld);
            GameWindow(const GameWorld &world,
                       sf::Vector2f positionInScreen,
                       sf::Vector2f sizeInScreen,
                       sf::Vector2f positionInWorld,
                       sf::Vector2f sizeInWorld);
            GameWindow(const GameWorld &world,
                       sf::Vector2f positionInWorld,
                       sf::Vector2f sizeInWorld,
                       float rotationInWorld);
            GameWindow(const GameWorld &world,
                       sf::Vector2f positionInScreen,
                       sf::Vector2f sizeInScreen);
    
            virtual void render();
    
            void setWorld(const GameWorld &newWorld);
            const GameWorld *getWorld();
    
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

            sf::View &getView();

        private:
            
            void updateView();
            bool verticalSort(Entity *, Entity *);
    
    };

}
