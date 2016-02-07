#include<SFML/Graphics.hpp>
#include<GameState.hpp>
#include<Entity.hpp>
#include<GameWorld.hpp>
#include<GameWindow.hpp>
#include"TestBox.hpp"

class TestEntityState : public sg::GameState {

    #define VEL 3.0f
    #define ROT 1.0f

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

            e0.setPosition(400.0f, -100.0f);
            e0.scale(0.5f, 0.5f);
            e1.fill(sf::Color::Red);
            e1.setPosition(400.0f, 0.0f);
            e0.addPossession(e1);

            e2.setPosition(400.0f, 100.0f);
            e2.scale(0.5f, 0.5f);
            e3.fill(sf::Color::Red);
            e3.setPosition(400.0f, 0.0f);
            e2.addPossession(e3);

            e4.setPosition(100.0f, 300.0f);
            e4.setScale(0.5f, 0.5f);
            e4.addPossession(e0);
            e4.addPossession(e2);

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

            accessInputManager().addAction(sf::Keyboard::Right,   [=](sf::Time t){moveRight1();});
            accessInputManager().addAction(sf::Keyboard::Left,    [=](sf::Time t){moveLeft1();});
            accessInputManager().addAction(sf::Keyboard::Up,      [=](sf::Time t){moveUp1();});
            accessInputManager().addAction(sf::Keyboard::Down,    [=](sf::Time t){moveDown1();});
            accessInputManager().addAction(sf::Keyboard::W,       [=](sf::Time t){moveUp0();});
            accessInputManager().addAction(sf::Keyboard::A,       [=](sf::Time t){moveLeft0();});
            accessInputManager().addAction(sf::Keyboard::S,       [=](sf::Time t){moveDown0();});
            accessInputManager().addAction(sf::Keyboard::D,       [=](sf::Time t){moveRight0();});
            accessInputManager().addAction(sf::Keyboard::Q,       [=](sf::Time t){rotateLeft0();});
            accessInputManager().addAction(sf::Keyboard::E,       [=](sf::Time t){rotateRight0();});
            accessInputManager().addAction(sf::Keyboard::Comma,   [=](sf::Time t){rotateLeft1();});
            accessInputManager().addAction(sf::Keyboard::Period,  [=](sf::Time t){rotateRight1();});
            accessInputManager().addAction(sf::Keyboard::Numpad6, [=](sf::Time t){moveRight4();});
            accessInputManager().addAction(sf::Keyboard::Numpad4, [=](sf::Time t){moveLeft4();});
            accessInputManager().addAction(sf::Keyboard::Numpad8, [=](sf::Time t){moveUp4();});
            accessInputManager().addAction(sf::Keyboard::Numpad2, [=](sf::Time t){moveDown4();});
            accessInputManager().addAction(sf::Keyboard::Numpad7, [=](sf::Time t){rotateLeft4();});
            accessInputManager().addAction(sf::Keyboard::Numpad9, [=](sf::Time t){rotateRight4();});
            accessInputManager().addAction(sf::Keyboard::C,       [=](sf::Time t){changeOwner();});

        }

        private:
            void moveUp0() {

                this->e0.move(0.0f, -VEL);

            }
            void moveLeft0() {

                this->e0.move(-VEL, 0.0f);

            }
            void moveDown0() {

                this->e0.move(0.0f, VEL);

            }
            void moveRight0() {

                this->e0.move(VEL, 0.0f);

            }
            void rotateLeft0() {

                this->e0.rotate(-ROT);

            }
            void rotateRight0() {

                this->e0.rotate(ROT);

            }
            void moveUp1() {

                this->e1.move(0.0f, -VEL);

            }
            void moveLeft1() {

                this->e1.move(-VEL, 0.0f);

            }
            void moveDown1() {

                this->e1.move(0.0f, VEL);

            }
            void moveRight1() {

                this->e1.move(VEL, 0.0f);

            }
            void rotateLeft1() {

                this->e1.rotate(-ROT);

            }
            void rotateRight1() {

                this->e1.rotate(ROT);

            }
            void moveUp4() {

                this->e4.move(0.0f, -VEL);

            }
            void moveLeft4() {

                this->e4.move(-VEL, 0.0f);

            }
            void moveDown4() {

                this->e4.move(0.0f, VEL);

            }
            void moveRight4() {

                this->e4.move(VEL, 0.0f);

            }
            void rotateLeft4() {

                this->e4.rotate(-ROT);

            }
            void rotateRight4() {

                this->e4.rotate(ROT);

            }
            void changeOwner() {

                static bool once = true;
                if (once) {
                    once = false;
                    this->e0.rotate(e4.getRotation());
                    this->e0.scale(e4.getScale());
                    this->e0.setPosition(this->e4.getTransform().transformPoint(this->e0.getPosition()));
                    this->e4.rotate(-e0.getRotation());
                    this->e4.scale(1.0f / e0.getScale().x, 1.0f / e0.getScale().y);
                    this->e4.setPosition(this->e1.getInverseTransform().transformPoint(this->e4.getPosition()));
                    this->e4.removePossession(this->e0);
                    this->e0.addPossession(this->e4);
                }

            }

};
