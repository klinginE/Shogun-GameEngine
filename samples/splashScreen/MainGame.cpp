//Shogun Includes
#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Management/StateManager.hpp>

//SFML Includes
#include <SFML/Graphics.hpp>

//solCrusade Includes
#include "MainGame.hpp"
#include "TitleState.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
const bool MainGame::IS_WINDOWS = true;
const std::string MainGame::PATH_DELIM = "\\";
#else
const bool MainGame::IS_WINDOWS = false;
const std::string MainGame::PATH_DELIM = "/";
#endif

const std::string MainGame::RESOURCE_PATH = "resources";
const std::string MainGame::FONTS_DIR = "fonts";
const std::string MainGame::IMAGES_DIR = "images";

const std::string MainGame::GAME_NAME = "MyGame";

const sf::Vector2u MainGame::GAME_SIZE_SMALL = MainGame::getScreenSize(false);
const sf::Vector2u MainGame::GAME_SIZE_FULL = MainGame::getScreenSize(true);

sf::Vector2u MainGame::getScreenSize(bool fullScreen) {

    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    if (fullScreen)
        return sf::Vector2u(vm.width, vm.height);

    return sf::Vector2u(static_cast<uint32_t>(static_cast<float>(vm.width) * SCREEN_PERCENTAGE),
                        static_cast<uint32_t>(static_cast<float>(vm.height) * SCREEN_PERCENTAGE));

}

int main(int argc, char *argv[]) {

    sg::GameLoop::inst().init(MainGame::GAME_SIZE_SMALL,
                              MainGame::GAME_NAME);
    TitleState ts;
    sg::StateManager::inst().pushState(ts);
    sg::GameLoop::inst().start();

    return 0;

}
