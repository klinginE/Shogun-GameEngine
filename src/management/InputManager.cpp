#include <map>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "InputManager.hpp"

namespace sg {
    
    InputManager::InputManager() {
    }
    
    void InputManager::addAction(sf::Keyboard::Key key, std::function<void()> callback) {
        
        actions[key] = callback;
    
    }
    
    void InputManager::clearAction(sf::Keyboard::Key key) {
    
        actions.erase(key);
    
    }
    
    std::function<void()> InputManager::getAction(sf::Keyboard::Key key) {
    
        return actions[key];
    
    }
    
    void InputManager::processInput() {
    
        for (auto iter=actions.begin(); iter!=actions.end(); ++iter) {
            
            sf::Keyboard::Key key = (sf::Keyboard::Key) iter->first;
            auto callback = iter->second;

            if (sf::Keyboard::isKeyPressed(key)) {
    
                callback(); // call callback function
    
            }
    
        }
    
    }

}
