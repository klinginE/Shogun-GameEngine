#pragma once

#include<SFML/Graphics.hpp>
#include<Shogun/Management/GameState.hpp>
#include<Shogun/Elements/Entity.hpp>
#include<Shogun/Management/GameWorld.hpp>
#include<Shogun/Management/Layer.hpp>
#include<Shogun/Management/GameWindow.hpp>
#include"TestBox.hpp"

#include <iostream>

class TestEntityState : public sg::GameState {

    #define VEL 3.0f
    #define ROT 1.0f
    #define FAC 1.025f

    private:
        sf::Font font;
        sf::Texture t;
        TestBox e0 = TestBox();
        TestBox e1 = TestBox();
        TestBox e2 = TestBox();
        sf::Sprite sprite = sf::Sprite();
        sf::ConvexShape rectangleShape0;
        sf::Text text;
        sf::ConvexShape rectangleShape1;
        sg::Layer l;
        sg::GameWorld world0;
        sg::GameWindow window0;
        sg::InputManager myInputManager;
        bool moveGlobal = true;

    public:
        TestEntityState() :
        sg::GameState()
        {
            t.loadFromFile("villager.png");
            sprite.setTexture(t);
            sprite.setTextureRect(sf::IntRect(2, 1, 11, 15));
            sprite.setOrigin(8.0f, 8.0f);
            sprite.scale(10.0f, 10.0f);
            sprite.setPosition(250.0f, 0.0f);
            sprite.rotate(-45.0f);
            e0.addDrawable(sprite, false);

            sf::FloatRect spriteBounds = sprite.getLocalBounds();
            rectangleShape0.setPointCount(4);
            rectangleShape0.setPoint(0, sf::Vector2f(spriteBounds.left + 3.0f, spriteBounds.top + 2.0f));
            rectangleShape0.setPoint(1, sf::Vector2f(spriteBounds.left + 8.0f, spriteBounds.top + 2.0f));
            rectangleShape0.setPoint(2, sf::Vector2f(spriteBounds.left + 8.0f, spriteBounds.top + 10.0f));
            rectangleShape0.setPoint(3, sf::Vector2f(spriteBounds.left + 3.0f, spriteBounds.top + 10.0f));
            rectangleShape0.setOrigin(sprite.getOrigin());
            rectangleShape0.setPosition(sprite.getPosition());
            rectangleShape0.setRotation(sprite.getRotation());
            rectangleShape0.setScale(sprite.getScale());
            rectangleShape0.setFillColor(sf::Color::Transparent);
            rectangleShape0.setOutlineColor(sf::Color::Yellow);
            rectangleShape0.setOutlineThickness(0.1f);

            e0.addTransformable(rectangleShape0, true);

            font.loadFromFile("arial.ttf");
            text.setFont(font);
            text.setString("Hello World!");
            text.setOrigin(100.0f, 80.0f);
            text.setPosition(5.0f, 250.0f);
            text.rotate(15.0f);
            text.scale(0.5f, 5.0f);
            text.setStyle(sf::Text::Regular);
            text.setColor(sf::Color::White);
            e0.addDrawable(text, true);

            sf::FloatRect textBounds = text.getLocalBounds();

            rectangleShape1.setPointCount(4);
            rectangleShape1.setPoint(0, sf::Vector2f(textBounds.left, textBounds.top));
            rectangleShape1.setPoint(1, sf::Vector2f(textBounds.left + textBounds.width, textBounds.top));
            rectangleShape1.setPoint(2, sf::Vector2f(textBounds.left + textBounds.width, textBounds.top + textBounds.height));
            rectangleShape1.setPoint(3, sf::Vector2f(textBounds.left, textBounds.top + textBounds.height));
            rectangleShape1.setOrigin(text.getOrigin());
            rectangleShape1.setPosition(text.getPosition());
            rectangleShape1.setRotation(text.getRotation());
            rectangleShape1.setScale(text.getScale());

            rectangleShape1.setFillColor(sf::Color::Transparent);
            rectangleShape1.setOutlineColor(sf::Color::Yellow);
            rectangleShape1.setOutlineThickness(1.0f);
            // e0.addDrawable(rectangleShape1, false);

            e0.setPosition(100.0f, 100.0f);
            e0.scale(0.5f, 0.5f);
            e0.setOrigin(10.0, 10.0f);

            e1.setPosition(400.0f, 100.0f);
            e1.scale(0.5f, 0.5f);
            e1.setOrigin(25.0, 20.0f);

            e2.setPosition(300.0f, 500.0f);
            e2.setScale(0.5f, 0.5f);

            
            l.addDynamicEntity(e0);
            l.addDynamicEntity(e1);
            l.addDynamicEntity(e2);
            world0.addLayer(0, l);

            window0.setSizeInWorld(sf::Vector2f(static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().x),
                                                static_cast<float>(sg::GameLoop::inst().getRenderWindow().getSize().y)));
            window0.setPosInWorld(window0.getSizeInWorld() / 2.0f);
            window0.setWorld(world0);
            //window0.setRenderOrder([=](const sg::Entity &e1, const sg::Entity &e2)->bool{return e1.getPosition().y > e2.getPosition().y;});

            this->addWindow(window0);
            this->addWorld(world0);

            this->myInputManager.addAction(sf::Event::EventType::KeyReleased, [=](const sf::Time t, const sf::Event e)
            {
                if (e.key.code == sf::Keyboard::C)
                {
                    changeOwner(t);
                }
                if (e.key.code == sf::Keyboard::R)
                {
                    removeOwner(t);
                }
                if (e.key.code == sf::Keyboard::G)
                {
                    this->moveGlobal = !this->moveGlobal;
                }
            });
            this->setInputManager(this->myInputManager);
        }
        void update(const sf::Time &tslu)
        {
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
            sg::GameState::update(tslu);
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
