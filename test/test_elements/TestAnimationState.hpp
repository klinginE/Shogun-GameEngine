#pragma once

#include<SFML/Graphics.hpp>
#include<Shogun/Management/GameState.hpp>
#include<Shogun/Elements/Entity.hpp>
#include<Shogun/Management/GameWorld.hpp>
#include<Shogun/Management/GameWindow.hpp>

class TestAnimationState : public sg::GameState {

    private:
        sf::Texture t;
        sg::Entity player = sg::Entity();
        sg::AnimatedSprite as = sg::AnimatedSprite();
        sf::ConvexShape rs;
        sg::GameWorld world0;
        sg::GameWindow window0;
        sg::InputManager myInputManger;
        sf::IntRect textRect0 = sf::IntRect(0, 0, 16, 16);
        sf::IntRect textRect1 = sf::IntRect(0, 16, 16, 16);
        sf::IntRect textRect2 = sf::IntRect(0, 32, 16, 16);
        sf::IntRect textRect3 = sf::IntRect(0, 48, 16, 16);

    public:
        TestAnimationState() :
        sg::GameState()
        {

            t.loadFromFile("villager.png");
            as.setTexture(t);
            as.setFrameDelay(sf::milliseconds(200));
            rs.setPointCount(4);
            rs.setPoint(0, sf::Vector2f(0.0f, 0.0f));
            rs.setPoint(1, sf::Vector2f(11.0f, 0.0f));
            rs.setPoint(2, sf::Vector2f(11.0f, 8.0f));
            rs.setPoint(3, sf::Vector2f(0.0f, 8.0f));
            rs.setOrigin(11.0f/2.0f, 4.0f);
            rs.setPosition(2.0f + 11.0f / 2.0f, 12.0f);

            as.setTextureRect(textRect0);
            as.addFrame(textRect0, rs);
            as.addFrame(textRect1, rs);
            as.addFrame(textRect2, rs);
            as.addFrame(textRect3, rs);
            as.addFrame(textRect1, rs);
            as.addFrame(textRect2, rs);
            as.addFrame(textRect0, rs);
            as.addFrame(textRect1, rs);
            as.addFrame(textRect2, rs);
            as.start();
            player.setPosition(sg::GameLoop::inst().getRenderWindow().getSize().x / 2.0f - 8.0f,
                               sg::GameLoop::inst().getRenderWindow().getSize().y / 2.0f - 8.0f);
            player.setOrigin(8.0f, 8.0f);
            player.scale(4.0f, 4.0f);
            player.addDrawable(as);

            world0.addEntity(player);

            window0.setSizeInWorld(sf::Vector2f(static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().x),
                                                static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().y)));
            window0.setPosInWorld(window0.getSizeInWorld() / 2.0f);
            window0.setWorld(world0);

            this->addWindow(window0);
            this->addWorld(world0);
            this->myInputManger.addAction(sf::Event::EventType::KeyReleased, [=](const sf::Time t, const sf::Event e) {
                if (e.key.code == sf::Keyboard::P)
                    sg::StateManager::inst().popState();
            });
            this->setInputManager(this->myInputManger);

        }
        void update(const sf::Time &tslu) {

            sg::GameState::update(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                moveRight(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                moveLeft(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                moveUp(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                moveDown(tslu);

        }

    private:
        void moveUp(const sf::Time &t) {

            this->player.move(0.0f, -VEL);

        }
        void moveLeft(const sf::Time &t) {

            this->player.move(-VEL, 0.0f);

        }
        void moveDown(const sf::Time &t) {

            this->player.move(0.0f, VEL);

        }
        void moveRight(const sf::Time &t) {

            this->player.move(VEL, 0.0f);

        }

};
