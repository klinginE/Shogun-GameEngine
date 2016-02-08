#include<SFML/Graphics.hpp>
#include<GameState.hpp>
#include<Entity.hpp>
#include<GameWorld.hpp>
#include<GameWindow.hpp>
#include"TestBox.hpp"

class TestEntityState : public sg::GameState {

    #define VEL 3.0f
    #define ROT 1.0f
    #define FAC 1.025f

    private:
        TestBox e0 = TestBox();
        TestBox e1 = TestBox();
        TestBox e2 = TestBox();
        TestBox e3 = TestBox();
        TestBox e4 = TestBox();
        sg::GameWorld world0;
        sg::GameWindow window0;
        sg::InputManager inputManager;

    public:
        TestEntityState() :
        sg::GameState()
        {

            e0.setPosition(100.0f, 100.0f);
            e0.scale(0.5f, 0.5f);

            e1.fill(sf::Color::Red);
            e1.setPosition(400.0f, 100.0f);
            e1.scale(0.5f, 0.5f);
            //e0.addPossession(e1);

            e2.setPosition(100.0f, 300.0f);
            e2.scale(0.5f, 0.5f);

            e3.fill(sf::Color::Red);
            e3.setPosition(400.0f, 300.0f);
            e3.scale(0.5f, 0.5f);
            //e2.addPossession(e3);

            e4.setPosition(300.0f, 500.0f);
            e4.setScale(0.5f, 0.5f);
            //e4.addPossession(e0);
            //e4.addPossession(e2);

            world0.addEntity(e0);
            world0.addEntity(e1);
            world0.addEntity(e2);
            world0.addEntity(e3);
            world0.addEntity(e4);

            window0.setSizeInWorld(sf::Vector2f(static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().x),
                                                static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().y)));
            window0.setPosInWorld(window0.getSizeInWorld() / 2.0f);
            window0.setWorld(world0);

            this->addWindow(window0);
            this->addWorld(world0);

            this->inputManager.addAction(sf::Keyboard::Right,   [=](sf::Time t){moveRight1(t);});
            this->inputManager.addAction(sf::Keyboard::Left,    [=](sf::Time t){moveLeft1(t);});
            this->inputManager.addAction(sf::Keyboard::Up,      [=](sf::Time t){moveUp1(t);});
            this->inputManager.addAction(sf::Keyboard::Down,    [=](sf::Time t){moveDown1(t);});
            this->inputManager.addAction(sf::Keyboard::W,       [=](sf::Time t){moveUp0(t);});
            this->inputManager.addAction(sf::Keyboard::A,       [=](sf::Time t){moveLeft0(t);});
            this->inputManager.addAction(sf::Keyboard::S,       [=](sf::Time t){moveDown0(t);});
            this->inputManager.addAction(sf::Keyboard::D,       [=](sf::Time t){moveRight0(t);});
            this->inputManager.addAction(sf::Keyboard::Q,       [=](sf::Time t){rotateLeft0(t);});
            this->inputManager.addAction(sf::Keyboard::E,       [=](sf::Time t){rotateRight0(t);});
            this->inputManager.addAction(sf::Keyboard::Comma,   [=](sf::Time t){rotateLeft1(t);});
            this->inputManager.addAction(sf::Keyboard::Period,  [=](sf::Time t){rotateRight1(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad6, [=](sf::Time t){moveRight4(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad4, [=](sf::Time t){moveLeft4(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad8, [=](sf::Time t){moveUp4(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad2, [=](sf::Time t){moveDown4(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad7, [=](sf::Time t){rotateLeft4(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad9, [=](sf::Time t){rotateRight4(t);});
            this->inputManager.addAction(sf::Keyboard::C,       [=](sf::Time t){changeOwner(t);});
            this->inputManager.addAction(sf::Keyboard::R,       [=](sf::Time t){removeOwner(t);});
            this->inputManager.addAction(sf::Keyboard::Z,       [=](sf::Time t){shrink0(t);});
            this->inputManager.addAction(sf::Keyboard::X,       [=](sf::Time t){grow0(t);});
            this->inputManager.addAction(sf::Keyboard::N,       [=](sf::Time t){shrink1(t);});
            this->inputManager.addAction(sf::Keyboard::M,       [=](sf::Time t){grow1(t);});
            this->setInputManager(this->inputManager);

        }

        private:
            void moveUp0(sf::Time t) {

                this->e0.move(0.0f, -VEL);

            }
            void moveLeft0(sf::Time t) {

                this->e0.move(-VEL, 0.0f);

            }
            void moveDown0(sf::Time t) {

                this->e0.move(0.0f, VEL);

            }
            void moveRight0(sf::Time t) {

                this->e0.move(VEL, 0.0f);

            }
            void rotateLeft0(sf::Time t) {

                this->e0.rotate(-ROT);

            }
            void rotateRight0(sf::Time t) {

                this->e0.rotate(ROT);

            }
            void moveUp1(sf::Time t) {

                this->e1.move(0.0f, -VEL);

            }
            void moveLeft1(sf::Time t) {

                this->e1.move(-VEL, 0.0f);

            }
            void moveDown1(sf::Time t) {

                this->e1.move(0.0f, VEL);

            }
            void moveRight1(sf::Time t) {

                this->e1.move(VEL, 0.0f);

            }
            void rotateLeft1(sf::Time t) {

                this->e1.rotate(-ROT);

            }
            void rotateRight1(sf::Time t) {

                this->e1.rotate(ROT);

            }
            void moveUp4(sf::Time t) {

                this->e4.move(0.0f, -VEL);

            }
            void moveLeft4(sf::Time t) {

                this->e4.move(-VEL, 0.0f);

            }
            void moveDown4(sf::Time t) {

                this->e4.move(0.0f, VEL);

            }
            void moveRight4(sf::Time t) {

                this->e4.move(VEL, 0.0f);

            }
            void rotateLeft4(sf::Time t) {

                this->e4.rotate(-ROT);

            }
            void rotateRight4(sf::Time t) {

                this->e4.rotate(ROT);

            }
            void changeOwner(sf::Time t) {

                static bool changeOnce = true;
                if (changeOnce) {
                    changeOnce = false;
                    this->e0.addPossession(this->e1);
                    this->e1.addPossession(this->e2);
                }

            }
            void removeOwner(sf::Time t) {

                static bool removeOnce = true;
                if (removeOnce) {
                    removeOnce = false;
                    this->e1.removePossession(this->e2);
                    this->e0.removePossession(this->e1);
                }

            }
            void shrink0(sf::Time t) {

                this->e0.scale(1.0f/FAC, 1.0f/FAC);

            }
            void grow0(sf::Time t) {

                this->e0.scale(FAC, FAC);

            }
            void shrink1(sf::Time t) {

                this->e1.scale(1.0f/FAC, 1.0f/FAC);

            }
            void grow1(sf::Time t) {

                this->e1.scale(FAC, FAC);

            }

};
