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
        sf::Texture t;
        sg::Entity player = sg::Entity();
        sg::AnimatedSprite as = sg::AnimatedSprite();
        sf::ConvexShape rs;
        sg::BoundingShape bounds;
        sf::IntRect textRect0 = sf::IntRect(0, 0, 16, 16);
        sf::IntRect textRect1 = sf::IntRect(0, 16, 16, 16);
        sf::IntRect textRect2 = sf::IntRect(0, 32, 16, 16);
        sf::IntRect textRect3 = sf::IntRect(0, 48, 16, 16);
        sg::GameWorld world0;
        sg::GameWindow window0;
        sg::InputManager inputManager;

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

            bounds.addShape(rs);

            as.setTextureRect(textRect0);
            as.addFrame(textRect0, bounds);
            as.addFrame(textRect1, bounds);
            as.addFrame(textRect2, bounds);
            as.addFrame(textRect3, bounds);
            as.addFrame(textRect1, bounds);
            as.addFrame(textRect2, bounds);
            as.addFrame(textRect0, bounds);
            as.addFrame(textRect1, bounds);
            as.addFrame(textRect2, bounds);
            as.start();
            player.setPosition(sg::GameLoop::inst().getRenderWindow().getSize().x / 2.0f - 8.0f,
                               sg::GameLoop::inst().getRenderWindow().getSize().y / 2.0f - 8.0f);
            player.setOrigin(8.0f, 8.0f);
            player.scale(4.0f, 4.0f);
            player.addDrawable(as);

            e0.addPossession(player);

            world0.addEntity(e0);
            world0.addEntity(e1);
            world0.addEntity(e2);
            world0.addEntity(player);

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
            this->inputManager.addAction(sf::Keyboard::Numpad6, [=](sf::Time t){moveRight2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad4, [=](sf::Time t){moveLeft2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad8, [=](sf::Time t){moveUp2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad2, [=](sf::Time t){moveDown2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad7, [=](sf::Time t){rotateLeft2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad9, [=](sf::Time t){rotateRight2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad1, [=](sf::Time t){shrink2(t);});
            this->inputManager.addAction(sf::Keyboard::Numpad3, [=](sf::Time t){grow2(t);});
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

                this->e0.moveGlobally(0.0f, -VEL);

            }
            void moveLeft0(sf::Time t) {

                this->e0.moveGlobally(-VEL, 0.0f);

            }
            void moveDown0(sf::Time t) {

                this->e0.moveGlobally(0.0f, VEL);

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

                this->e1.moveGlobally(0.0f, -VEL);

            }
            void moveLeft1(sf::Time t) {

                this->e1.moveGlobally(-VEL, 0.0f);

            }
            void moveDown1(sf::Time t) {

                this->e1.moveGlobally(0.0f, VEL);

            }
            void moveRight1(sf::Time t) {

                this->e1.moveGlobally(VEL, 0.0f);

            }
            void rotateLeft1(sf::Time t) {

                this->e1.rotate(-ROT);

            }
            void rotateRight1(sf::Time t) {

                this->e1.rotate(ROT);

            }
            void moveUp2(sf::Time t) {

                this->e2.moveGlobally(0.0f, -VEL);

            }
            void moveLeft2(sf::Time t) {

                this->e2.moveGlobally(-VEL, 0.0f);

            }
            void moveDown2(sf::Time t) {

                this->e2.moveGlobally(0.0f, VEL);

            }
            void moveRight2(sf::Time t) {

                this->e2.moveGlobally(VEL, 0.0f);

            }
            void rotateLeft2(sf::Time t) {

                this->e2.rotate(-ROT);

            }
            void rotateRight2(sf::Time t) {

                this->e2.rotate(ROT);

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
            void shrink2(sf::Time t) {

                this->e2.scale(1.0f/FAC, 1.0f/FAC);

            }
            void grow2(sf::Time t) {

                this->e2.scale(FAC, FAC);

            }

};
