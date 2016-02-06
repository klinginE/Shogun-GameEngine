#pragma once

#include <map>
#include <set>
#include <functional>
#include <SFML/Graphics.hpp>

/* TODO: We need a way to handle mouse input as well as keyboard input
 *       Currently, this implementation handles only keyboard input.
 */

namespace sg {

//    struct funcStuff {
//        functype_t funcType;
//
//        union f {
//            std::function<void()> basic,
//            std::function<void(sf::Time)> withT
//        };
//    };

    class InputManager {
        
        std::map<sf::Keyboard::Key, std::function<void(sf::Time)>> actions;
    
        public:
            InputManager();
    
            void addAction(sf::Keyboard::Key key, std::function<void(sf::Time)> callback);
            void clearAction(sf::Keyboard::Key key);
            std::function<void(sf::Time)> getAction(sf::Keyboard::Key key);
            void processInput(const sf::Time &);
    
    };
    
}
