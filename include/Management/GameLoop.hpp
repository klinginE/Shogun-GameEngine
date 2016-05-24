#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

namespace sg {
    
    class GameLoop {
    
        public:
            static GameLoop & inst();
            
            void init(const sf::Vector2u &windowDimensions,
                      const sf::String &windowName,
                      uint32_t style=sf::Style::Close | sf::Style::Titlebar,
                      const sf::ContextSettings &settings=sf::ContextSettings());
    
            void start();

            sf::RenderWindow & getRenderWindow();

            void pause();
            void resume();
            bool isPaused();

            ~GameLoop() {}
    
        private:
            
            sf::RenderWindow window;
            bool paused = false;
    
            GameLoop() {}
            GameLoop(GameLoop const&) = delete;
            void operator=(GameLoop const&) = delete;
    };
}
