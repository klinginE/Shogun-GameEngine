#include <Shogun/Elements/BoundingShape.hpp>
#include <Shogun/Elements/AnimatedSprite.hpp>
#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Management/GameState.hpp>
#include <Shogun/Management/StateManager.hpp>
#include <Shogun/Management/GameWindow.hpp>
#include <Shogun/Management/GameWorld.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>

sg::Entity entities[10];
sg::GameWorld gameWorld;
void testGameWorld() {

    std::cout << std::endl;
    std::cout << "Testing GameWorld" << std::endl;
    std::cout << std::endl;

    // Test init
    assert(gameWorld.getEntities().size() == 0);

    std::cout << "gameWorld size starts at 0" << std::endl;

    gameWorld.update(sf::Time());

    std::cout << "Updating empty gameWorld works." << std::endl;

    // Test add entities and getEntities
    for (std::size_t i = 0; i < 10; i++) {
        std::size_t old_size = gameWorld.getEntities().size();
        gameWorld.addEntity(entities[i]);
        std::cout << "Adding an entity: old size = " << old_size
                  << ", new size = " << gameWorld.getEntities().size() << std::endl;
        assert(gameWorld.getEntities().size() == i + 1);
    }

    // Test delete entities and getEntities
    for (std::size_t i = 0; i < 10; i++) {
        std::size_t old_size = gameWorld.getEntities().size();
        entities[i].setDeletionStatus(true);
        gameWorld.update(sf::Time());
        std::cout << "Removing an entity: old size = " << old_size
                  << ", new size = " << gameWorld.getEntities().size() << std::endl;
        assert(gameWorld.getEntities().size() == 9 - i);
    }

    // Test activate/deactivate collisions
    std::cout << "Initial collision status = " << gameWorld.getCollisionStatus() << std::endl;
    gameWorld.deactivateCollisions();
    std::cout << "Deactivating collisions: collision status = " << gameWorld.getCollisionStatus() << std::endl;
    assert(gameWorld.getCollisionStatus() == false);
    gameWorld.activateCollisions();
    std::cout << "Activating collisions: collision status = " << gameWorld.getCollisionStatus() << std::endl;
    assert(gameWorld.getCollisionStatus() == true);

    // Test activate/deactivate scanline
    std::cout << "Initial scanline status = " << ((gameWorld.getScanlineStatus() == sg::scanline_t::VERTICAL) ? "VERTICAL" : "HORIZONTAL") << std::endl;
    gameWorld.setVerticalScanline();
    std::cout << "Setting vertical scanline: scanline status = " << ((gameWorld.getScanlineStatus() == sg::scanline_t::VERTICAL) ? "VERTICAL" : "HORIZONTAL") << std::endl;
    assert(gameWorld.getScanlineStatus() == sg::scanline_t::VERTICAL);
    gameWorld.setHorizontalScanline();
    std::cout << "Setting horizontal scanline: scanline status = " << ((gameWorld.getScanlineStatus() == sg::scanline_t::VERTICAL) ? "VERTICAL" : "HORIZONTAL") << std::endl;
    assert(gameWorld.getScanlineStatus() == sg::scanline_t::HORIZONTAL);

}

sg::GameWindow gameWindow;
void testGameWindow() {

    std::cout << std::endl;
    std::cout << "Testing GameWindow" << std::endl;
    std::cout << std::endl;

    // Test initial gameWindow
    std::cout << "Default initial gameWindow world: " << ((gameWindow.getWorld() == NULL) ? "NULL" : "NOT NULL") << std::endl;
    assert(gameWindow.getWorld() == NULL);

    std::cout << "Default initial gameWindow posInScreen: " << gameWindow.getPosInScreen().x << ", " << gameWindow.getPosInScreen().y << std::endl;

    std::cout << "Default initial gameWindow sizeInScreen: " << gameWindow.getSizeInScreen().x << ", " << gameWindow.getSizeInScreen().y << std::endl;

    std::cout << "Default initial gameWindow posInWorld: " << gameWindow.getPosInWorld().x << ", " << gameWindow.getPosInWorld().y << std::endl;

    std::cout << "Default initial gameWindow sizeInWorld: " << gameWindow.getSizeInWorld().x << ", " << gameWindow.getSizeInWorld().y << std::endl;

    std::cout << "Default initial gameWindow rotInWorld: " << gameWindow.getRotInWorld() << std::endl;

    // Test rendering with initial gameWindow
    gameWindow.render();
    std::cout << "Successfully rendered with initial gameWindow" << std::endl;

    // Test setting world
    gameWindow.setWorld(gameWorld);
    std::cout << "gameWindow world after setting world: " << ((gameWindow.getWorld() == &gameWorld) ? "SUCCESS" : "UNSUCCESSFUL") << std::endl;
    assert(gameWindow.getWorld() == &gameWorld);

    // Test rendering with initial gameWindow after setting world
    gameWindow.render();
    std::cout << "Successfully rendered after adding world" << std::endl;

    // Test setPosInScreen
    gameWindow.setPosInScreen(sf::Vector2f(0.5, 0.25));
    assert(gameWindow.getPosInScreen() == sf::Vector2f(0.5, 0.25));

    // Test setSizeInScreen
    gameWindow.setSizeInScreen(sf::Vector2f(0.1, 0.3));
    assert(gameWindow.getSizeInScreen() == sf::Vector2f(0.1, 0.3));

    // Test setPosInWorld
    gameWindow.setPosInWorld(sf::Vector2f(500, 250));
    assert(gameWindow.getPosInWorld() == sf::Vector2f(500, 250));

    // Test setSizeInWorld
    gameWindow.setSizeInWorld(sf::Vector2f(250, 500));
    assert(gameWindow.getSizeInWorld() == sf::Vector2f(250, 500));

    // Test setRotInWorld
    gameWindow.setRotInWorld(50);
    assert(gameWindow.getRotInWorld() == 50);

}

sg::GameState gameState;
sg::InputManager inputManager;
void testGameState() {

    std::cout << std::endl;
    std::cout << "Testing GameWindow" << std::endl;
    std::cout << std::endl;

    assert(gameState.getWindow(0) == NULL);
    assert(gameState.getWorld(0) == NULL);
    assert(gameState.getNumWindows() == 0);
    assert(gameState.getNumWorlds() == 0);
    assert(gameState.getInputManager() == NULL);
    assert(gameState.removeWindow(0) == NULL);
    assert(gameState.removeWorld(0) == NULL);

    gameState.addWindow(gameWindow);
    assert(gameState.getWindow(0) == &gameWindow);
    assert(gameState.getWindow(1) == NULL);
    assert(gameState.getNumWindows() == 1);
    assert(gameState.removeWindow(1) == NULL);
    assert(gameState.removeWindow(0) == &gameWindow);

    gameState.addWorld(gameWorld);
    assert(gameState.getWorld(0) == &gameWorld);
    assert(gameState.getWorld(1) == NULL);
    assert(gameState.getNumWorlds() == 1);
    assert(gameState.removeWorld(1) == NULL);
    assert(gameState.removeWorld(0) == &gameWorld);

    gameState.setInputManager(inputManager);
    assert(gameState.getInputManager() == &inputManager);
    assert(gameState.removeInputManager() == &inputManager);
    assert(gameState.getInputManager() == NULL);
    assert(gameState.removeInputManager() == NULL);

}

int main() {

    testGameWorld();
    testGameWindow();
    testGameState();
    std::cout << "Success!" << std::endl;

    return 0;

}
