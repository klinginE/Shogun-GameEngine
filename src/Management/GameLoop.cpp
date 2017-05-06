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

    GameLoop &GameLoop::inst() {

        static GameLoop instance;

        return instance;

    }

    void GameLoop::start() {

        sf::Clock clock;

        sf::Clock fpsClock;
        sf::Time currTime = sf::Time::Zero;
        uint32_t count = 0;

        sf::Clock uc;
        sf::Clock rc;
        sf::Clock ec;
        uint64_t totalTime = 0;
        while (getRenderWindow().isOpen()) {

            totalTime = 0;
            if ((count++ % 10) == 0) {

                currTime = fpsClock.restart();
                float fps = 10.0f / currTime.asSeconds();
                std::cout << std::endl << "FPS: " << fps << std::endl;
                fpsClock.restart();

            }
            // elapsed time
            sf::Time elapsed = clock.restart();

            // check if there is a current state
            GameState *topState;
            if ((topState = StateManager::inst().peekState()) == NULL) {

                getRenderWindow().close();
                break;

            }

            // handle window events
            ec.restart();
            sf::Event event;
            while (getRenderWindow().pollEvent(event)) {

                const InputManager *topIM = NULL;
                if ((topIM = topState->getInputManager()))
                    for (const auto &a : topIM->getAction(event.type))
                        a(elapsed, event);

                if (event.type == sf::Event::Closed)
                    getRenderWindow().close();

            }
            sf::Time et = ec.restart();
            totalTime += et.asMicroseconds();
            if ((count % 10) == 0)
                std::cout << "Total event time:       " << et.asMicroseconds() << std::endl;

            if (!this->paused) {

                uc.restart();
                topState->update(elapsed);
                sf::Time ut = uc.restart();
                totalTime += ut.asMicroseconds();
                if ((count % 10) == 0)
                    std::cout << "Total update time:      " << ut.asMicroseconds() << std::endl;

                rc.restart();
                topState->render();
                sf::Time rt = rc.restart();
                totalTime += rt.asMicroseconds();
                if ((count % 10) == 0)
                    std::cout << "Total render time:      " << rt.asMicroseconds() << std::endl;

            }
            //std::cout << "Total time:             " << totalTime << std::endl;
            //std::cout << "estimate number of fps: " << (1.0 / (static_cast<double>(1e-6) * static_cast<double>(totalTime))) << std::endl << std::endl;

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
        getRenderWindow().create(
                setWindowDimensions,
                windowName, style, settings);
        getRenderWindow().setPosition(windowPosition);
        getRenderWindow().setSize(windowDimensions);
        getRenderWindow().setVerticalSyncEnabled(true);
        getRenderWindow().setFramerateLimit(0);

        /*sf::Image icon;
        std::string path = "../resources/images/icon/Sol.png";
        icon.loadFromFile(path);
        std::cout << path << " x: " << icon.getSize().x << " y: " << icon.getSize().y << std::endl;
        std::cout << "ptr: " << (void *)icon.getPixelsPtr() << std::endl << std::endl;
        getRenderWindow().setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());*/

    }

    sf::RenderWindow &GameLoop::getRenderWindow() {

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
