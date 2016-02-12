#include<Entity.hpp>
#include<SFML/Graphics.hpp>

class TestBox : public sg::Entity {

    private:
        sf::RectangleShape r0;
        sf::CircleShape r1;
        sf::RectangleShape r2;
        sf::CircleShape r3;
        sg::BoundingShape bs;
        void handleCollision(const sg::Entity &otherE, const std::vector<sf::Vector2f> &collisionVs) {

            sg::Entity::handleCollision(otherE, collisionVs);
            if (this->r0.getFillColor() == sf::Color::White)
                this->fill(sf::Color::Yellow);
            else if (this->r0.getFillColor() == sf::Color::Yellow)
                this->fill(sf::Color::White);
            else if (this->r0.getFillColor() == sf::Color::Red)
                this->fill(sf::Color::Green);
            else if (this->r0.getFillColor() == sf::Color::Green)
                this->fill(sf::Color::Red);

        }
    
    public:
        TestBox() :
        sg::Entity()
        {

            r0.setSize(sf::Vector2f(100.0f, 50.0f));
            r0.setOrigin(50.0f, 25.0f);
            this->addDrawable(r0, false);
            bs.addShape(r0);
            r1.setRadius(40.0f);
            r1.setOrigin(40.0f, 40.0f);
            r1.move(100.0f, 0.0f);
            r1.scale(2.0f, 1.0f);
            this->addDrawable(r1, false);
            bs.addShape(r1);
            r2.setSize(sf::Vector2f(250.0f, 10.0f));
            r2.setOrigin(125.0f, 5.0f);
            r2.rotate(-90.0f);
            this->addDrawable(r2, false);
            bs.addShape(r2);
            r3.setRadius(40.0f);
            r3.setOrigin(40.0f, 40.0f);
            r3.move(-100.0f, 0.0f);
            this->addDrawable(r3, false);
            bs.addShape(r3);
            this->addTransformable(bs);

        }
        TestBox(bool isCollidable) :
        sg::Entity(isCollidable)
        {

            r0.setSize(sf::Vector2f(100.0f, 50.0f));
            r0.setOrigin(50.0f, 25.0f);
            this->addDrawable(r0, false);
            bs.addShape(r0);
            r1.setRadius(40.0f);
            r1.setOrigin(40.0f, 40.0f);
            r1.move(100.0f, 0.0f);
            r1.scale(2.0f, 1.0f);
            this->addDrawable(r1, false);
            bs.addShape(r1);
            r2.setSize(sf::Vector2f(250.0f, 10.0f));
            r2.setOrigin(125.0f, 5.0f);
            r2.rotate(-90.0f);
            this->addDrawable(r2, false);
            bs.addShape(r2);
            r3.setRadius(40.0f);
            r3.setOrigin(40.0f, 40.0f);
            r3.move(-100.0f, 0.0f);
            this->addDrawable(r3, false);
            bs.addShape(r3);
            //bs.rotate(-45.0f);
            this->addTransformable(bs);
            //this->rotate(45.0f);

        }

        void fill(const sf::Color &c) {

            this->r0.setFillColor(c);
            this->r1.setFillColor(c);
            this->r2.setFillColor(c);
            this->r3.setFillColor(c);

        }
        const sf::Color &getFill() {

            return this->r0.getFillColor();

        }

};
