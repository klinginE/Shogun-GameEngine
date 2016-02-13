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

#define NUM_ENEMIES 100
#define WORLD_HEIGHT 1000
#define WORLD_WIDTH 1000

// Local includes
#include "Ball.hpp"

class RunState : public sg::GameState {

    sg::GameWorld world;
    sg::GameWindow p1Window;
    sg::GameWindow p2Window;
    sg::InputManager inputManager;

    sg::GameWindow splitBarWindow;
    sg::GameWorld splitBarWorld;
    sg::Entity splitBar;
    sf::RectangleShape splitBarRect;

    Ball p1;
    Ball p2;
    Ball enemies[NUM_ENEMIES];

    sf::RectangleShape edge;
    sg::Entity edgeEntity;

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
            p1.setPosition(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                           std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2);
            p2.setPosition(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                           std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2);
            //Make sure the horizontal distance between p1 and p2 is far enough
            uint32_t iterations = 0;
            while (std::abs(p2.getPosition().x - p1.getPosition().x) < WORLD_WIDTH/4 && iterations < 1000) {

                p2.setPosition(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                               std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2);
                iterations++;

            }

            p1.setColor(sf::Color::Red);
            p2.setColor(sf::Color::Blue);
            world.addEntity(p1);
            world.addEntity(p2);
            for (int i = 0; i < NUM_ENEMIES; i++) {
                enemies[i].setMass(enemies[i].getMass()/2);
                enemies[i].setPosition(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                                       std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2);
                enemies[i].setColor(sf::Color::Green);
                world.addEntity(enemies[i]);
            }
            world.activateCollisions();

            // Create edge bounds and add to world
            edge.setSize(sf::Vector2f(WORLD_WIDTH+20,
                                      WORLD_HEIGHT+20));
            edge.setPosition(-sf::Vector2f((WORLD_WIDTH+20)/2.0f,
                                           (WORLD_HEIGHT+20)/2.0f));
            edge.setFillColor(sf::Color::Transparent);
            edge.setOutlineColor(sf::Color::Yellow);
            edge.setOutlineThickness(10.0f);
            edgeEntity.addDrawable(edge, false);
            edgeEntity.setIsCollidable(false);
            world.addEntity(edgeEntity);

            // Add player1 input
            inputManager.addAction(sf::Keyboard::W, [=](sf::Time t){p1.moveUp(t, edge);});
            inputManager.addAction(sf::Keyboard::A, [=](sf::Time t){p1.moveLeft(t, edge);});
            inputManager.addAction(sf::Keyboard::S, [=](sf::Time t){p1.moveDown(t, edge);});
            inputManager.addAction(sf::Keyboard::D, [=](sf::Time t){p1.moveRight(t, edge);});

            // Add player2 input
            inputManager.addAction(sf::Keyboard::Up, [=](sf::Time t){p2.moveUp(t, edge);});
            inputManager.addAction(sf::Keyboard::Left, [=](sf::Time t){p2.moveLeft(t, edge);});
            inputManager.addAction(sf::Keyboard::Down, [=](sf::Time t){p2.moveDown(t, edge);});
            inputManager.addAction(sf::Keyboard::Right, [=](sf::Time t){p2.moveRight(t, edge);});

            // Create split bar down middle of screen
            splitBarWindow.setWorld(splitBarWorld);
            splitBarWindow.setPosInScreen(sf::Vector2f(0.499f, 0.0f));
            splitBarWindow.setSizeInScreen(sf::Vector2f(0.002f, 1.0f));
            splitBarWindow.setPosInWorld(sf::Vector2f(splitBarWindow.getSizeInWorld().x/2,
                                                      splitBarWindow.getSizeInWorld().y/2));
            splitBarRect.setSize(splitBarWindow.getSizeInWorld());
            splitBar.addDrawable(splitBarRect);
            splitBarWorld.addEntity(splitBar);

            // Add game world, windows, and input manager
            addWorld(world);
            addWindow(p1Window);
            addWindow(p2Window);
            addWindow(splitBarWindow);
            setInputManager(inputManager);

        };

};
