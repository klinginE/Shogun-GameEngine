#pragma once

#include <stdlib.h>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Shogun/Management/GameWorld.hpp>

namespace sg {
    
    class GameWindow {
    
        sf::Vector2f positionInScreen;
        sf::Vector2f sizeInScreen;
        sf::Vector2f positionInWorld;
        sf::Vector2f sizeInWorld;
        float rotationInWorld;
        const GameWorld *world;
        sf::View view;
        std::function<bool(const Entity &, const Entity &)>
                renderOrder;
    
        public:
            GameWindow();
            GameWindow(const GameWorld &world);
            GameWindow(const GameWorld &world,
                       const sf::Vector2f &positionInScreen,
                       const sf::Vector2f &sizeInScreen,
                       const sf::Vector2f &positionInWorld,
                       const sf::Vector2f &sizeInWorld,
                       float rotationInWorld);
            GameWindow(const GameWorld &world,
                       const sf::Vector2f &positionInScreen,
                       const sf::Vector2f &sizeInScreen,
                       const sf::Vector2f &positionInWorld,
                       const sf::Vector2f &sizeInWorld);
            GameWindow(const GameWorld &world,
                       const sf::Vector2f &positionInWorld,
                       const sf::Vector2f &sizeInWorld,
                       float rotationInWorld);
            GameWindow(const GameWorld &world,
                       const sf::Vector2f &positionInScreen,
                       const sf::Vector2f &sizeInScreen);
    
            virtual void render();
    
            void setWorld(const GameWorld &newWorld);
            const GameWorld *getWorld() const;
    
            void setPosInScreen(const sf::Vector2f &positionInScreen);
            sf::Vector2f getPosInScreen() const;
    
            void setSizeInScreen(const sf::Vector2f &sizeInScreen);
            sf::Vector2f getSizeInScreen() const;
    
            void setPosInWorld(const sf::Vector2f &posInWorld);
            sf::Vector2f getPosInWorld() const;
    
            void setSizeInWorld(const sf::Vector2f &sizeInWorld);
            sf::Vector2f getSizeInWorld() const;
    
            void setRotInWorld(float rotationInWorld);
            float getRotInWorld() const;

            sf::Vector2f worldCoordToScreenCoord(sf::Vector2f) const;
            sf::Vector2f screenCoordToWorldCoord(sf::Vector2f) const;

            const sf::View * getView() const;

            void setRenderOrder(std::function<bool(const Entity &, const Entity &)>);

        private:
            
            void updateView();

    };

}
