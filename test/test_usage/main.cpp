// Shogun libraries
#include <GameLoop.hpp>
#include <StateManager.hpp>

// SFML libraries
#include <SFML/Graphics.hpp>

// Local includes
#include "TestState.hpp"

#include <stdio.h>

int main() {

    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2u(600, 600),
                              sf::String("Test"));

    // Initialize states
    TestState testState;
    sg::StateManager::inst().pushState(testState);

    // Start gameloop
    sg::GameLoop::inst().start();

    return 0;

}
