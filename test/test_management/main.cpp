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

}

int main() {

    testGameWorld();
    std::cout << "Success!" << std::endl;

    return 0;

}
