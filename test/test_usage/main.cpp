#include "../../src/management/GameLoop.hpp"

int main() {

    // Initialize states


    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2i(200, 200),
                              sf::String("Test"));

    // Start gameloop
    sg::GameLoop::inst().start();

    return 0;

}
