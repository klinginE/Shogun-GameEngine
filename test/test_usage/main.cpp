// Shogun libraries
#include <GameLoop.hpp>
#include <StateManager.hpp>

// SFML libraries
#include <SFML/Graphics.hpp>

// Local includes
#include "TestState.hpp"

int main() {

    // Initialize states
    TestState testState;
    sg::StateManager::inst().pushState(&testState);

    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2i(200, 200),
                              sf::String("Test"));

    // Start gameloop
    sg::GameLoop::inst().start();

    return 0;

}
