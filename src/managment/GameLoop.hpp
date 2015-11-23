#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <stack>
#include <SFML/Graphics.hpp>

class GameLoop {

    public:
        static GameLoop & inst();
        
        void init(sf::Vector2i windowDimensions,
                  sf::String windowName);

        void start();

        sf::RenderWindow & getRenderWindow();

        ~GameLoop();

    private:
        
        sf::RenderWindow window;

        GameLoop() {};
        GameLoop(GameLoop const&) = delete;
        void operator=(GameLoop const&) = delete;
        bool paused = false;
};

#endif /* GAME_HPP */
