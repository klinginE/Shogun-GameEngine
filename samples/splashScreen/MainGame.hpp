#pragma once

//c++ includes
#include <string>

#define SCREEN_PERCENTAGE 0.85f

class MainGame {

    public:
        static const bool IS_WINDOWS;
        static const std::string PATH_DELIM;

        static const std::string RESOURCE_PATH;
        static const std::string FONTS_DIR;
        static const std::string IMAGES_DIR;

        static const std::string GAME_NAME;

        static const sf::Vector2u GAME_SIZE_SMALL;
        static const sf::Vector2u GAME_SIZE_FULL;

    private:
        static sf::Vector2u getScreenSize(bool);

};
