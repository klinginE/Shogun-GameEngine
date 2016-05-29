#include <Shogun/Management/InputManager.hpp>

namespace sg {

    void InputManager::addAction(sf::Event::EventType type, std::function<void(const sf::Time, const sf::Event)> callback) {

        actions[type].push_back(callback);

    }

    void InputManager::clearAction(sf::Event::EventType type) {

        actions.erase(type);

    }

    const std::vector<std::function<void(const sf::Time, const sf::Event)>> InputManager::getAction(sf::Event::EventType type) const {

        if (this->actions.find(type) == this->actions.end()) {

            std::vector<std::function<void(const sf::Time, const sf::Event)>> v;
            return v;

        }
        return this->actions.find(type)->second;

    }

}
