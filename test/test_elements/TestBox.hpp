#pragma once

#include<Shogun/Elements/Entity.hpp>
#include<SFML/Graphics.hpp>

class TestBox : public sg::Entity
{
    private:
        sf::RectangleShape r0;
        sf::CircleShape r1;
        sf::RectangleShape r2;
        sf::CircleShape r3;
        void handleCollision(Entity &otherE,
                             const std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f> &collisionMap)
        {
            this->fill(sf::Color::Red);
        }

    public:
        TestBox() :
        sg::Entity()
        {
            this->commonInit();
        }

        TestBox(bool isCollidable) :
        sg::Entity(isCollidable)
        {
            this->commonInit();
        }

        void commonInit()
        {
            r0.setSize(sf::Vector2f(100.0f, 50.0f));
            r0.setOrigin(50.0f, 25.0f);
            this->addDrawable(r0);

            r1.setRadius(40.0f);
            r1.setOrigin(40.0f, 40.0f);
            r1.move(100.0f, 0.0f);
            r1.scale(2.0f, 1.0f);
            this->addDrawable(r1);

            r2.setSize(sf::Vector2f(250.0f, 10.0f));
            r2.setOrigin(125.0f, 5.0f);
            r2.rotate(-90.0f);
            this->addDrawable(r2);

            r3.setRadius(40.0f);
            r3.setOrigin(40.0f, 40.0f);
            r3.move(-100.0f, 0.0f);
            this->addDrawable(r3);

            this->setOrigin(5.0f, 10.0f);
        }

        void update(sf::Time tslu)
        {
            Entity::update(tslu);
            this->fill(sf::Color::Green);
        }

        void fill(const sf::Color &c)
        {
            this->r0.setFillColor(c);
            this->r1.setFillColor(c);
            this->r2.setFillColor(c);
            this->r3.setFillColor(c);
        }

        const sf::Color &getFill()
        {
            return this->r0.getFillColor();
        }
};
