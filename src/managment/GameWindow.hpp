#pragma once

#include <SFML/Vector2.hpp>

#include "GameWorld.hpp"

namespace sg {
    
    class GameWindow {
    
        Vector2f positionInScreen;
        Vector2f sizeInScreen;
        Vector2f positionInWorld;
        Vector2f sizeInWorld;
        float rotationInWorld;
        GameWorld *world;
        sf::View view;
    
        public:
            GameWindow(GameWorld *world);
            GameWindow(GameWorld *world,
                       Vector2f positionInScreen,
                       Vector2f sizeInScreen,
                       Vector2f positionInWorld,
                       Vector2f sizeInWorld,
                       float rotationInWorld);
            GameWindow(GameWorld *world,
                       Vector2f positionInScreen,
                       Vector2f sizeInScreen,
                       Vector2f positionInWorld,
                       Vector2f sizeInWorld);
            GameWindow(GameWorld *world,
                       Vector2f positionInWorld,
                       Vector2f sizeInWorld,
                       float rotationInWorld);
            GameWindow(GameWorld *world,
                       Vector2f positionInScreen,
                       Vector2f sizeInScreen);
    
            void render();
    
            void setWorld(GameWorld *newWorld);
            GameWorld *getWorld();
    
            void setPosInScreen(Vector2f positionInScreen);
            Vector2f getPosInScreen();
    
            void setSizeInScreen(Vector2f sizeInScreen);
            Vector2f getSizeInScreen();
    
            void setPosInWorld(Vector2f posInWorld);
            Vector2f getPosInWorld();
    
            void setSizeInWorld(Vector2f sizeInWorld);
            Vector2f getSizeInWorld();
    
            void setRotInWorld(float rotationInWorld);
            float getRotInWorld();
    
        private:
            
            void updateView();
    
    };

}
