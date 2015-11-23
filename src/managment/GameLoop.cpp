#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameLoop.hpp"
#include "StateManager.hpp"
#include "GameState.hpp"

GameLoop & GameLoop::inst() {

    static Game instance;
    
    return instance;

}

void GameLoop::start() {

    sf::Clock clock;

    while (getRenderWindow().isOpen()) {

        // handle window close event
        sf::Event event;
        while (getRenderWindow().pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                getRenderWindow().close();

        }

        // elapsed time
        sf::Time elapsed = clock.restart();

        // process current state
        if (peekState() == NULL) break;
       
        StateManager.inst().peekState()->handleInput();
        StateManager.inst().peekState()->update(elapsed);
        StateManager.inst().peekState()->draw();

    }

}

void GameLoop::init(sf::Vector2i windowDimensions,
                sf::String windowName) {

    // Configure
    sf::VideoMode setWindowDimensions(
            windowDimensions.x,
            windowDimensions.y);

    sf::Vector2i windowPosition(
            static_cast<int>(
                sf::VideoMode::getDesktopMode().width / 2.0f -
                setWindowDimensions.width / 2.0f),
            static_cast<int>(
                sf::VideoMode::getDesktopMode().height / 2.0f -
                setWindowDimensions.height / 2.0f));

    int windowStyleBitmask = sf::Style::Close   |
                             sf::Style::Titlebar;

    // Setup
    getRenderWindow().create(setWindowDimensions,
            windowName, windowStyleBitmask);
    getRenderWindow().setPosition(windowPosition);
    getRenderWindow().setVerticalSyncEnabled(true);
    getRenderWindow().setFramerateLimit(60);

}

sf::RenderWindow & GameLoop::getRenderWindow() {

    return window;

}

GameLoop::~GameLoop() {

    // do nothing

}


