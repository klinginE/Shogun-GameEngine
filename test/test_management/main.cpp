#include<BoundingShape.hpp>
#include<AnimatedSprite.hpp>
#include<GameLoop.hpp>
#include<GameState.hpp>
#include<StateManager.hpp>
#include<GameWindow.hpp>
#include<GameWorld.hpp>
#include<Entity.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<assert.h>

sg::Entity entities[10];
sg::GameWorld gameWorld;
void testGameWorld() {

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

    // Test initial gameWindow
    std::cout << "Default initial gameWindow world: " << ((gameWindow.getWorld() == NULL) ? "NULL" : "NOT NULL") << std::endl;
    assert(gameWindow.getWorld() == NULL);

    std::cout << "Default initial gameWindow posInScreen: " << gameWindow.getPosInScreen().x << ", " << gameWindow.getPosInScreen().y << std::endl;

    std::cout << "Default initial gameWindow sizeInScreen: " << gameWindow.getSizeInScreen().x << ", " << gameWindow.getSizeInScreen().y << std::endl;

    std::cout << "Default initial gameWindow posInWorld: " << gameWindow.getPosInWorld().x << ", " << gameWindow.getPosInWorld().y << std::endl;

    std::cout << "Default initial gameWindow sizeInWorld: " << gameWindow.getSizeInWorld().x << ", " << gameWindow.getSizeInWorld().y << std::endl;

    // Test rendering with initial gameWindow
    gameWindow.render();

}

int main() {

//    testGameWorld();
    testGameWindow();
    std::cout << "Success!" << std::endl;

    return 0;

}
