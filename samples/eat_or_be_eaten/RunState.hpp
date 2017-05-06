#pragma once

// Standard includes
#include <stdio.h>

// SFML includes
#include <SFML/Graphics.hpp>

// Shougun includes
#include <Shogun/Management/GameState.hpp>
#include <Shogun/Management/GameWorld.hpp>
#include <Shogun/Management/Layer.hpp>
#include <Shogun/Management/GameWindow.hpp>
#include <Shogun/Management/InputManager.hpp>
#include <Shogun/Elements/Entity.hpp>

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
    sg::Layer layer;
    sg::Layer splitBarLayer;
    sg::Entity splitBar;
    sf::RectangleShape splitBarRect;

    Ball p1;
    Ball p2;
    Ball enemies[NUM_ENEMIES];

    sf::RectangleShape edge;
    sg::Entity edgeEntity;

    public:
        RunState() :
        sg::GameState()
        {

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
            layer.addDynamicEntity(p1);
            layer.addDynamicEntity(p2);
            for (int i = 0; i < NUM_ENEMIES; i++) {
                enemies[i].setMass(enemies[i].getMass()/2);
                enemies[i].setPosition(std::rand() % WORLD_WIDTH - WORLD_WIDTH/2,
                                       std::rand() % WORLD_HEIGHT - WORLD_HEIGHT/2);
                enemies[i].setColor(sf::Color::Green);
                layer.addStaticEntity(enemies[i]);
            }

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
            layer.addStaticEntity(edgeEntity);
            world.addLayer(0, layer);

            // Create split bar down middle of screen
            splitBarWindow.setWorld(splitBarWorld);
            splitBarWindow.setPosInScreen(sf::Vector2f(0.499f, 0.0f));
            splitBarWindow.setSizeInScreen(sf::Vector2f(0.002f, 1.0f));
            splitBarWindow.setPosInWorld(sf::Vector2f(splitBarWindow.getSizeInWorld().x/2,
                                                      splitBarWindow.getSizeInWorld().y/2));
            splitBarRect.setSize(splitBarWindow.getSizeInWorld());
            splitBar.addDrawable(splitBarRect);
            splitBarLayer.addStaticEntity(splitBar);
	    splitBarWorld.addLayer(0, splitBarLayer);

            // Add game world, windows, and input manager
            addWorld(world);
            addWindow(p1Window);
            addWindow(p2Window);
            addWindow(splitBarWindow);
            setInputManager(inputManager);

        }

        void update(const sf::Time &tslu) {

            // Add player1 input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                p1.moveUp(tslu, edge);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                p1.moveLeft(tslu, edge);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                p1.moveDown(tslu, edge);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                p1.moveRight(tslu, edge);

            // Add player2 input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                p2.moveUp(tslu, edge);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                p2.moveLeft(tslu, edge);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                p2.moveDown(tslu, edge);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                p2.moveRight(tslu, edge);

            sg::GameState::update(tslu);

        }

};
