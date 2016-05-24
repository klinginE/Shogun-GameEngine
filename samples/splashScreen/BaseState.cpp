#include "BaseState.hpp"

BaseState::BaseState() :
sg::GameState()
{

    this->im.addAction(sf::Event::EventType::KeyPressed, [=](const sf::Time t, const sf::Event e) {
        if (e.key.code == sf::Keyboard::Escape) {

            sf::Vector2u size = sg::GameLoop::inst().getRenderWindow().getSize();
            if (size == MainGame::GAME_SIZE_FULL)
                sg::GameLoop::inst().init(MainGame::GAME_SIZE_SMALL,
                                          MainGame::GAME_NAME);
            else
                sg::GameLoop::inst().init(MainGame::GAME_SIZE_FULL,
                                          MainGame::GAME_NAME,
                                          sf::Style::Fullscreen);

        }
    });
    this->im.addAction(sf::Event::EventType::LostFocus, [=](const sf::Time t, const sf::Event e) {
        sg::GameLoop::inst().pause();
    });
    this->im.addAction(sf::Event::EventType::GainedFocus, [=](const sf::Time t, const sf::Event e) {
        sg::GameLoop::inst().unpause();
    });
    this->setInputManager(this->im);

}
