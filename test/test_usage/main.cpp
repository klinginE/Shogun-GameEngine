// Shogun libraries
#include <GameLoop.hpp>
#include <StateManager.hpp>

// SFML libraries
#include <SFML/Graphics.hpp>

// Local includes
#include "TestState.hpp"

#include <stdio.h>

int main() {

    // Initialize states
    TestState testState;
    sg::StateManager::inst().pushState(&testState);

    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2u(600, 600),
                              sf::String("Test"));

    std::cout << "RenderWindow size: "
              << sg::GameLoop::inst().getRenderWindow().getSize().x
              << ", "
              << sg::GameLoop::inst().getRenderWindow().getSize().y
              << std::endl;


    // Start gameloop
    sg::GameLoop::inst().start();

    return 0;

}
