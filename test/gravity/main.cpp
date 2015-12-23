// Shogun libraries
#include <GameLoop.hpp>
#include <StateManager.hpp>
#include <GameState.hpp>

// SFML libraries
#include <SFML/Graphics.hpp>

// Local includes
#include "RunState.hpp"

#include <stdio.h>

int main() {

    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2u(600, 600),
                              sf::String("Test"));

    // Initialize states
    RunState runState;
    sg::StateManager::inst().pushState(
            dynamic_cast<sg::GameState *>(&runState));

    // Start gameloop
    sg::GameLoop::inst().start();

    return 0;

}
