#pragma once

#include<SFML/Graphics.hpp>
#include<Shogun/GameState.hpp>
#include<Shogun/Entity.hpp>
#include<Shogun/GameWorld.hpp>
#include<Shogun/GameWindow.hpp>
#include"TestBox.hpp"

class TestEntityState : public sg::GameState {

    #define VEL 3.0f
    #define ROT 1.0f
    #define FAC 1.025f

    private:
        TestBox e0 = TestBox();
        TestBox e1 = TestBox();
        TestBox e2 = TestBox();
        sg::GameWorld world0;
        sg::GameWindow window0;
        sg::InputManager myInputManager;
        bool moveGlobal = true;

    public:
        TestEntityState() :
        sg::GameState()
        {

            e0.setPosition(100.0f, 100.0f);
            e0.scale(0.5f, 0.5f);
            e0.setOrigin(10.0, 10.0f);

            e1.fill(sf::Color::Red);
            e1.setPosition(400.0f, 100.0f);
            e1.scale(0.5f, 0.5f);
            e1.setOrigin(25.0, 20.0f);

            e2.setPosition(300.0f, 500.0f);
            e2.setScale(0.5f, 0.5f);

            world0.addEntity(e0);
            world0.addEntity(e1);
            world0.addEntity(e2);

            window0.setSizeInWorld(sf::Vector2f(static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().x),
                                                static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().y)));
            window0.setPosInWorld(window0.getSizeInWorld() / 2.0f);
            window0.setWorld(world0);
            window0.setRenderOrder([=](const sg::Entity &e1, const sg::Entity &e2)->bool{return e1.getPosition().y > e2.getPosition().y;});

            this->addWindow(window0);
            this->addWorld(world0);

            this->myInputManager.addAction(sf::Event::EventType::KeyReleased, [=](const sf::Time t, const sf::Event e) {
                if (e.key.code == sf::Keyboard::C)
                    changeOwner(t);
                if (e.key.code == sf::Keyboard::R)
                    removeOwner(t);
                if (e.key.code == sf::Keyboard::G)
                    this->moveGlobal = !this->moveGlobal;
            });
            this->setInputManager(this->myInputManager);

        }
        void update(const sf::Time &tslu) {

            sg::GameState::update(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                moveRight1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                moveLeft1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                moveUp1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                moveDown1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                moveUp0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                moveLeft0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                moveDown0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                moveRight0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                rotateLeft0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                rotateRight0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
                rotateLeft1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
                rotateRight1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
                moveRight2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
                moveLeft2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
                moveUp2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
                moveDown2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
                rotateLeft2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
                rotateRight2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
                shrink2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
                grow2(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                shrink0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                grow0(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                shrink1(tslu);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                grow1(tslu);

        }

    private:
        void moveUp0(const sf::Time &t) {

            if (this->moveGlobal)
                this->e0.moveGlobally(0.0f, -VEL);
            else
                this->e0.move(0.0f, -VEL);

        }
        void moveLeft0(const sf::Time &t) {

            if (this->moveGlobal)
                this->e0.moveGlobally(-VEL, 0.0f);
            else
                this->e0.move(-VEL, 0.0f);

        }
        void moveDown0(const sf::Time &t) {

            if (this->moveGlobal)
                this->e0.moveGlobally(0.0f, VEL);
            else
                this->e0.move(0.0f, VEL);

        }
        void moveRight0(const sf::Time &t) {

            if (this->moveGlobal)
                this->e0.moveGlobally(VEL, 0.0f);
            else
                this->e0.move(VEL, 0.0f);

        }
        void rotateLeft0(const sf::Time &t) {

            this->e0.rotate(-ROT);

        }
        void rotateRight0(sf::Time t) {

            this->e0.rotate(ROT);

        }
        void moveUp1(const sf::Time &t) {

            if (this->moveGlobal)
                this->e1.moveGlobally(0.0f, -VEL);
            else
                this->e1.move(0.0f, -VEL);

        }
        void moveLeft1(const sf::Time &t) {

            if (this->moveGlobal)
                this->e1.moveGlobally(-VEL, 0.0f);
            else
                this->e1.move(-VEL, 0.0f);

        }
        void moveDown1(const sf::Time &t) {

            if (this->moveGlobal)
                this->e1.moveGlobally(0.0f, VEL);
            else
                this->e1.move(0.0f, VEL);

        }
        void moveRight1(const sf::Time &t) {

            if (this->moveGlobal)
                this->e1.moveGlobally(VEL, 0.0f);
            else
                this->e1.move(VEL, 0.0f);

        }
        void rotateLeft1(const sf::Time &t) {

            this->e1.rotate(-ROT);

        }
        void rotateRight1(const sf::Time &t) {

            this->e1.rotate(ROT);

        }
        void moveUp2(const sf::Time &t) {

            if (this->moveGlobal)
                this->e2.moveGlobally(0.0f, -VEL);
            else
                this->e2.move(0.0f, -VEL);

        }
        void moveLeft2(const sf::Time &t) {

            if (this->moveGlobal)
                this->e2.moveGlobally(-VEL, 0.0f);
            else
                this->e2.move(-VEL, 0.0f);

        }
        void moveDown2(const sf::Time &t) {

            if (this->moveGlobal)
                this->e2.moveGlobally(0.0f, VEL);
            else
                this->e2.move(0.0f, VEL);

        }
        void moveRight2(const sf::Time &t) {

            if (this->moveGlobal)
                this->e2.moveGlobally(VEL, 0.0f);
            else
                this->e2.move(VEL, 0.0f);

        }
        void rotateLeft2(const sf::Time &t) {

            this->e2.rotate(-ROT);

        }
        void rotateRight2(const sf::Time &t) {

            this->e2.rotate(ROT);

        }
        void changeOwner(const sf::Time &t) {

            this->e0.addPossession(this->e1);
            this->e1.addPossession(this->e2);

        }
        void removeOwner(const sf::Time &t) {

            this->e1.removePossession(this->e2);
            this->e0.removePossession(this->e1);

        }
        void shrink0(const sf::Time &t) {

            this->e0.scale(1.0f/FAC, 1.0f/FAC);

        }
        void grow0(const sf::Time &t) {

            this->e0.scale(FAC, FAC);

        }
        void shrink1(const sf::Time &t) {

            this->e1.scale(1.0f/FAC, 1.0f/FAC);

        }
        void grow1(const sf::Time &t) {

            this->e1.scale(FAC, FAC);

        }
        void shrink2(const sf::Time &t) {

            this->e2.scale(1.0f/FAC, 1.0f/FAC);

        }
        void grow2(const sf::Time &t) {

            this->e2.scale(FAC, FAC);

        }

};
