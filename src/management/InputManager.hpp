#pragma once

#include <map>
#include <set>
#include <functional>
#include <SFML/Graphics.hpp>

/* TODO: We need a way to handle mouse input as well as keyboard input
 *       Currently, this implementation handles only keyboard input.
 */

namespace sg {

    class InputManager {
        
        std::map<sf::Keyboard::Key, std::function<void()>> actions;
    
        public:
            InputManager();
    
            void addAction(sf::Keyboard::Key key, std::function<void()> callback);
            void clearAction(sf::Keyboard::Key key);
            std::function<void()> getAction(sf::Keyboard::Key key);
            void processInput();
    
    };
    
}
