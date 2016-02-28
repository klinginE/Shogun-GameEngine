#include "InputManager.hpp"

namespace sg {

    void InputManager::addAction(sf::Event::EventType type, std::function<void(const sf::Time, const sf::Event)> callback) {

        actions[type] = callback;

    }

    void InputManager::clearAction(sf::Event::EventType type) {

        actions.erase(type);

    }

    std::function<void(const sf::Time, const sf::Event)> InputManager::getAction(sf::Event::EventType type) const {

        if (this->actions.find(type) == this->actions.end())
            return [=](const sf::Time t, const sf::Event e){};
        return this->actions.find(type)->second;

    }

}
