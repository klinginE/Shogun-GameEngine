#pragma once

// Shogun includes
#include <GameState.hpp>
#include <GameWorld.hpp>
#include <GameWindow.hpp>
#include <InputManager.hpp>
#include <Entity.hpp>

// Standard includes
#include <stdlib.h>
#include <stdio.h>

class TestState : public sg::GameState {
    
    sg::GameWorld world;
    sg::GameWindow window;
    sg::InputManager worldInput;
    sg::Entity entity;
    sf::Sprite entitySprite;
    sf::Texture entityTexture;
    sf::Uint8 pixels[200*200*4];

    public:
        TestState() {
            
            // Initialize entity with white box
            for (int i = 0; i < 200*200*4; i += 4) {
                pixels[i]   = 255; // R
                pixels[i+1] = 255; // G
                pixels[i+2] = 255; // B
                pixels[i+3] = 255; // A
            }
            entityTexture.create(200, 200);
            entityTexture.update(pixels);
            entitySprite.setTexture(entityTexture);
            entitySprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
            entity.addSprite(entitySprite);
            entity.move(sf::Vector2f(0, 0));

            // Initialize world
            world.addEntity(entity);

            // Initialize input
            worldInput.addAction(sf::Keyboard::Left,  [=](){moveLeft();});
            worldInput.addAction(sf::Keyboard::Right, [=](){moveRight();});
            worldInput.addAction(sf::Keyboard::Up,    [=](){moveUp();});
            worldInput.addAction(sf::Keyboard::Down,  [=](){moveDown();});
            world.setInputManager(worldInput);
            world.activateInput();
            
            // Initialize window
            window.setWorld(world);
            window.setSizeInWorld(sf::Vector2f((float) sg::GameLoop::inst().getRenderWindow().getSize().x,
                                               (float) sg::GameLoop::inst().getRenderWindow().getSize().y));

            std::cout << "Window SizeInWorld: "
                      << window.getSizeInWorld().x << ", "
                      << window.getSizeInWorld().y << std::endl;
            
            // add game world and window
            addWorld(world);
            addWindow(window);

        };

    private:
        // Entity movement functions
        void moveLeft() {
            sf::Vector2f transVec(-10, 0);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << " "
                      << "Bounds: "
                      << entity.getTextureBounds().left << ", "
                      << entity.getTextureBounds().top << ", "
                      << entity.getTextureBounds().width << ", "
                      << entity.getTextureBounds().height << std::endl;
        };
        void moveRight() {
            sf::Vector2f transVec(10, 0);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << " "
                      << "Bounds: "
                      << entity.getTextureBounds().left << ", "
                      << entity.getTextureBounds().top << ", "
                      << entity.getTextureBounds().width << ", "
                      << entity.getTextureBounds().height << std::endl;
        };
        void moveUp() {
            sf::Vector2f transVec(0, -10);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << " "
                      << "Bounds: "
                      << entity.getTextureBounds().left << ", "
                      << entity.getTextureBounds().top << ", "
                      << entity.getTextureBounds().width << ", "
                      << entity.getTextureBounds().height << std::endl;
        };
        void moveDown() {
            sf::Vector2f transVec(0, 10);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << " "
                      << "Bounds: "
                      << entity.getTextureBounds().left << ", "
                      << entity.getTextureBounds().top << ", "
                      << entity.getTextureBounds().width << ", "
                      << entity.getTextureBounds().height << std::endl;
        };

};

