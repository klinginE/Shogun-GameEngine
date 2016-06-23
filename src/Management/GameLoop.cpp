#include <stack>
#include <functional>
#include <sys/time.h>

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

            timespec ts0;
            timespec ts1;

            clock_gettime(CLOCK_REALTIME, &ts0);
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
                const std::vector<std::function<void(const sf::Time, const sf::Event)>> actions;
                if ((topIM = topState->getInputManager()))
                    for (const auto &a : topIM->getAction(event.type))
                        a(elapsed, event);

                if (event.type == sf::Event::Closed)
                    getRenderWindow().close();

            }
            clock_gettime(CLOCK_REALTIME, &ts1);
            std::cout << "ELT: " << (ts1.tv_nsec - ts0.tv_nsec) << std::endl;

            if (!this->paused) {

                clock_gettime(CLOCK_REALTIME, &ts0);
                topState->update(elapsed);
                clock_gettime(CLOCK_REALTIME, &ts1);
                std::cout << " UT: " << (ts1.tv_nsec - ts0.tv_nsec) << std::endl;

                clock_gettime(CLOCK_REALTIME, &ts0);
                topState->render();
                clock_gettime(CLOCK_REALTIME, &ts1);
                std::cout << " RT: " << (ts1.tv_nsec - ts0.tv_nsec) << std::endl << std::endl;

            }

        }

    }

    void GameLoop::init(const sf::Vector2u &windowDimensions,
                        const sf::String &windowName,
                        uint32_t style,
                        const sf::ContextSettings &settings) {
    
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

        // Setup
        getRenderWindow().create(setWindowDimensions,
                windowName, style, settings);
        getRenderWindow().setPosition(windowPosition);
        getRenderWindow().setSize(windowDimensions);
        getRenderWindow().setVerticalSyncEnabled(true);
        getRenderWindow().setFramerateLimit(60);
    
    }
    
    sf::RenderWindow & GameLoop::getRenderWindow() {
    
        return window;
    
    }

    void GameLoop::pause() {

        this->paused = true;

    }

    void GameLoop::resume() {

        this->paused = false;

    }

    bool GameLoop::isPaused() {

        return this->paused;

    }

}
