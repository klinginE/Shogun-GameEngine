#include <map>
#include <functional>

#include <SFML/Graphics.hpp>

#include "InputManager.hpp"

InputManager::InputManager() {
}

void InputManager::addAction(int key, std::function<void()> callback) {
    
    actions[key] = callback;

}

void InputManager::clearAction(int key) {

    actions.erase(key);

}

std::function<void()> InputManager::getAction(int key) {

    return actions[key];

}

void InputManager::processInput() {

    for (std::set<int>::iterator
         iter=keys.begin(); iter!=keys.end(); ++iter) {

        if (sf::Keyboard::isKeyPressed(*iter)) {

            actions[*iter](); // call callback function

        }

    }

}
