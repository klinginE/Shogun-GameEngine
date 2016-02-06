#include<SFML/Graphics.hpp>
#include<GameState.hpp>
#include<Entity.hpp>
#include<GameWorld.hpp>
#include<GameWindow.hpp>
#include"TestBox.hpp"

class TestEntityState : public sg::GameState {

    #define VEL 3.0f

    private:
        TestBox e0;
        TestBox *e1 = NULL;
        sg::GameWorld world0;
        sg::GameWindow window0;
        sg::InputManager inputManager;

    public:
        TestEntityState() :
        sg::GameState()
        {

            e0.setPosition(200.0f, 300.0f);
            e0.rotate(15.0f);
            e1 = new TestBox(true);
            e1->fill(sf::Color::Red);
            e1->setPosition(400.0f, 300.0f);
            e1->rotate(-90.0f);
            e0.addPossession(*e1);

            world0.addEntity(&e0);
            world0.addEntity(e1);

            window0.setSizeInWorld(sf::Vector2f(static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().x),
                                                static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().y)));
            window0.setPosInWorld(window0.getSizeInWorld() / 2.0f);
            window0.setWorld(&world0);

            addWindow(window0);
            addWorld(world0);

            inputManager.addAction(sf::Keyboard::Right, [=](){moveRight1();});
            inputManager.addAction(sf::Keyboard::Left,  [=](){moveLeft1();});
            inputManager.addAction(sf::Keyboard::Up,    [=](){moveUp1();});
            inputManager.addAction(sf::Keyboard::Down,  [=](){moveDown1();});
            inputManager.addAction(sf::Keyboard::W,     [=](){moveUp0();});
            inputManager.addAction(sf::Keyboard::A,     [=](){moveLeft0();});
            inputManager.addAction(sf::Keyboard::S,     [=](){moveDown0();});
            inputManager.addAction(sf::Keyboard::D,     [=](){moveRight0();});
            setInputManager(inputManager);

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
            void moveUp1() {

                this->e1->move(0.0f, -VEL);

            }
            void moveLeft1() {

                this->e1->move(-VEL, 0.0f);

            }
            void moveDown1() {

                this->e1->move(0.0f, VEL);

            }
            void moveRight1() {

                this->e1->move(VEL, 0.0f);

            }

};
