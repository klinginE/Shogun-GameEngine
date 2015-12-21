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
                pixels[i] = 0;     // R
                pixels[i+1] = 0;   // G
                pixels[i+2] = 0;   // B
                pixels[i+3] = 255; // A
            }
            entityTexture.create(200, 200);
            entityTexture.update(pixels);
            entitySprite.setTexture(entityTexture);
            entity.addSprite(entitySprite);

            // Initialize world
            world.addEntity(&entity);

            // Initialize input
            worldInput.addAction(sf::Keyboard::Left,  [=](){moveLeft();});
            worldInput.addAction(sf::Keyboard::Right, [=](){moveRight();});
            worldInput.addAction(sf::Keyboard::Up,    [=](){moveUp();});
            worldInput.addAction(sf::Keyboard::Down,  [=](){moveDown();});
            world.setInputManager(&worldInput);
            world.activateInput();
            
            // Initialize window
            window.setWorld(&world);
            
            // add game world and window
            accessGameWorlds().push_back(&world);
            accessGameWindows().push_back(&window);

        };

    private:
        // Entity movement functions
        void moveLeft() {
            sf::Vector2f transVec(-10, 0);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << std::endl;
        };
        void moveRight() {
            sf::Vector2f transVec(10, 0);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << std::endl;
        };
        void moveUp() {
            sf::Vector2f transVec(0, -10);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << std::endl;
        };
        void moveDown() {
            sf::Vector2f transVec(0, 10);
            entity.translate(transVec);
            std::cout << "New position: "
                      << entity.getPos().x << ", "
                      << entity.getPos().y << std::endl;
        };

};

