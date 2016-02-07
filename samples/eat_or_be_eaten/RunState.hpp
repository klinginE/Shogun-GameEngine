#pragma once

// Standard includes
#include <stdio.h>

// SFML includes
#include <SFML/Graphics.hpp>

// Shougun includes
#include <GameState.hpp>
#include <GameWorld.hpp>
#include <GameWindow.hpp>
#include <InputManager.hpp>
#include <Entity.hpp>

#define NUM_ENEMIES 10
#define WORLD_HEIGHT 1000
#define WORLD_WIDTH 1000

// Local includes
#include "Ball.hpp"

class RunState : public sg::GameState {

    sg::GameWorld world;
    sg::GameWindow p1Window;
    sg::GameWindow p2Window;
    sg::InputManager inputManager;

    Ball p1;
    Ball p2;
    Ball enemies[NUM_ENEMIES];

    public:
        RunState() {
            
            // Initialize windows
            p1.setMyWindow(p1Window);
            p2.setMyWindow(p2Window);
            p1Window.setWorld(world);
            p2Window.setWorld(world);
            p1Window.setPosInScreen(sf::Vector2f(0.0f, 0.0f));
            p1Window.setSizeInScreen(sf::Vector2f(0.5f, 1.0f));
            p2Window.setPosInScreen(sf::Vector2f(0.5f, 0.0f));
            p2Window.setSizeInScreen(sf::Vector2f(0.5f, 1.0f));

            sf::Vector2u renderWindowSize = sg::GameLoop::inst().getRenderWindow().getSize();

            p1Window.setSizeInWorld(sf::Vector2f(renderWindowSize.x/2,
                                                 renderWindowSize.y));
            p2Window.setSizeInWorld(sf::Vector2f(renderWindowSize.x/2,
                                                 renderWindowSize.y));

            // Add players and enemies to world
            p1.setPosition(sf::Vector2f(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                                        std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2));
            p2.setPosition(sf::Vector2f(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                                        std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2));
            world.addEntity(p1);
            world.addEntity(p2);
            for (int i = 0; i < NUM_ENEMIES; i++) {
                enemies[i].setPosition(
                        sf::Vector2f(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                                     std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2));
                world.addEntity(enemies[i]);
            }

            // Add player1 input
            inputManager.addAction(sf::Keyboard::W, [=](sf::Time t){p1.moveUp(t);});
            inputManager.addAction(sf::Keyboard::A, [=](sf::Time t){p1.moveLeft(t);});
            inputManager.addAction(sf::Keyboard::S, [=](sf::Time t){p1.moveDown(t);});
            inputManager.addAction(sf::Keyboard::D, [=](sf::Time t){p1.moveRight(t);});

            // Add player2 input
            inputManager.addAction(sf::Keyboard::Up, [=](sf::Time t){p2.moveUp(t);});
            inputManager.addAction(sf::Keyboard::Left, [=](sf::Time t){p2.moveLeft(t);});
            inputManager.addAction(sf::Keyboard::Down, [=](sf::Time t){p2.moveDown(t);});
            inputManager.addAction(sf::Keyboard::Right, [=](sf::Time t){p2.moveRight(t);});

            // Add game world, windows, and input manager
            addWorld(world);
            addWindow(p1Window);
            addWindow(p2Window);
            setInputManager(inputManager);

        };

};
