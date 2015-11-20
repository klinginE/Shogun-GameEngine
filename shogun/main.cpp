// SFML includes
#include <SFML/Graphics.hpp>

// Global includes
#include <string>
#include <iostream>
#include <typeinfo>

// Local includes
#include "ball.h"
#include "paddle.h"
#include "PlayState.hpp"
#include "TitleState.hpp"
#include "GameLoop.hpp"
#include "StateManager.hpp"

int main() {

    GameLoop::inst().init(
              sf::Vector2i(640,480),
              sf::String("Game"));

    TitleState titleState;
    StateManager::inst().pushState((GameState *) &titleState);

    GameLoop::inst().start();

    return 0;

}
