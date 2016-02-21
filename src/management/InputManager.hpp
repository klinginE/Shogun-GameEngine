#pragma once

//C++ includes
#include <map>
#include <functional>

//Shogun includes
#include <SFML/Graphics.hpp>

namespace sg {

    class InputManager {

        private:
            std::map<sf::Event::EventType, std::function<void(const sf::Time, const sf::Event)>> actions;

        public:
            void addAction(sf::Event::EventType, std::function<void(const sf::Time, const sf::Event)>);
            void clearAction(sf::Event::EventType);
            std::function<void(const sf::Time, const sf::Event)> getAction(sf::Event::EventType);
            void processInput(const sf::Event::EventType);

    };

}
