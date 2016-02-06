#pragma once

// Standard includes
#include <stdio.h>

// SFML includes
#include <SFML/Graphics.hpp>

// Shogun includes
#include <GameState.hpp>
#include <GameWorld.hpp>
#include <GameWindow.hpp>
#include <InputManager.hpp>
#include <Entity.hpp>

// Local includes
#include "Universe.hpp"

class RunState : public sg::GameState {

    Universe universe;
    sg::GameWindow window;
    sg::InputManager inputManager;
    
    public:
        RunState() {
            
            // Initialize window
            window.setWorld(universe);
            window.setSizeInWorld(sf::Vector2f((float) sg::GameLoop::inst().getRenderWindow().getSize().x*INITIAL_ZOOM,
                                               (float) sg::GameLoop::inst().getRenderWindow().getSize().y*INITIAL_ZOOM));

            // add game world and window
            addWorld(universe);
            addWindow(window);

            inputManager.addAction(sf::Keyboard::Right, [=](){increaseWindowSize();});
            inputManager.addAction(sf::Keyboard::Left,  [=](){decreaseWindowSize();});
            inputManager.addAction(sf::Keyboard::W,     [=](){moveUp();});
            inputManager.addAction(sf::Keyboard::A,     [=](){moveLeft();});
            inputManager.addAction(sf::Keyboard::S,     [=](){moveDown();});
            inputManager.addAction(sf::Keyboard::D,     [=](){moveRight();});
            setInputManager(inputManager);

        };

        void render() {
            
            universe.setMinDispRadius(MIN_DISP_RADIUS_RATIO*window.getSizeInWorld().x);

            sg::GameState::render();
        };

    private:
        void increaseWindowSize() {
            sf::Vector2f windowSize = window.getSizeInWorld();
            windowSize.x *= 1.05f;
            windowSize.y *= 1.05f;
            window.setSizeInWorld(windowSize);
        };

        void decreaseWindowSize() {
            sf::Vector2f windowSize = window.getSizeInWorld();
            windowSize.x /= 1.05f;
            windowSize.y /= 1.05f;
            window.setSizeInWorld(windowSize);
        };

        void moveLeft() {
            sf::Vector2f windowPos = window.getPosInWorld();
            windowPos.x -= window.getSizeInWorld().x*0.02;
            window.setPosInWorld(windowPos);
        };

        void moveRight() {
            sf::Vector2f windowPos = window.getPosInWorld();
            windowPos.x += window.getSizeInWorld().x*0.02;
            window.setPosInWorld(windowPos);
        };

        void moveUp() {
            sf::Vector2f windowPos = window.getPosInWorld();
            windowPos.y -= window.getSizeInWorld().y*0.02;
            window.setPosInWorld(windowPos);
        };

        void moveDown() {
            sf::Vector2f windowPos = window.getPosInWorld();
            windowPos.y += window.getSizeInWorld().y*0.02;
            window.setPosInWorld(windowPos);
        };

};
