#include <stack>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Management/StateManager.hpp>
#include <Shogun/Management/GameState.hpp>
#include <Shogun/Management/InputManager.hpp>

namespace sg {
    
    GameLoop & GameLoop::inst() {
    
        static GameLoop instance;
        
        return instance;
    
    }
    
    void GameLoop::start() {
    
        sf::Clock clock;
    
        while (getRenderWindow().isOpen()) {

            // elapsed time
            sf::Time elapsed = clock.restart();

            // check if there is a current state
            GameState *topState;
            if ((topState = StateManager::inst().peekState()) == NULL) {

                getRenderWindow().close();
                break;

            }

            // handle window events
            sf::Event event;
            while (getRenderWindow().pollEvent(event)) {

                const InputManager *topIM = NULL;
                std::function<void(const sf::Time, const sf::Event)> action;
                if ((topIM = topState->getInputManager()) &&
                    (action = topIM->getAction(event.type)))
                    action(elapsed, event);

                if (event.type == sf::Event::Closed)
                    getRenderWindow().close();

            }

            topState->update(elapsed);
            topState->render();

        }

    }

    void GameLoop::init(const sf::Vector2u &windowDimensions,
                        const sf::String &windowName) {
    
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
        getRenderWindow().setSize(windowDimensions);
        getRenderWindow().setVerticalSyncEnabled(true);
        getRenderWindow().setFramerateLimit(60);
    
    }
    
    sf::RenderWindow & GameLoop::getRenderWindow() {
    
        return window;
    
    }
    
    GameLoop::~GameLoop() {
    
        // do nothing
    
    }

}
