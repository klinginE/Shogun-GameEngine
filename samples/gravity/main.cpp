// Shogun libraries
#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Management/StateManager.hpp>
#include <Shogun/Management/GameState.hpp>

// SFML libraries
#include <SFML/Graphics.hpp>

// Local includes
#include "RunState.hpp"

#include <stdio.h>

int main() {

    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2u(600, 600),
                              sf::String("Gravity"));
    sg::GameLoop::inst().getRenderWindow().setFramerateLimit(60);

    // Initialize states
    RunState runState;
    sg::StateManager::inst().pushState(runState);

    // Start gameloop
    sg::GameLoop::inst().start();

    return 0;

}
