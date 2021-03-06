#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

namespace sg {
    
    class GameLoop {
    
        public:
            static GameLoop & inst();
            
            void init(const sf::Vector2u &windowDimensions,
                      const sf::String &windowName);
    
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
}
