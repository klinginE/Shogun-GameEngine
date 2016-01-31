#include<Entity.hpp>
#include<SFML/Graphics.hpp>

class TestBox : public sg::Entity {

    private:
        sf::RectangleShape r0;
        sf::CircleShape r1;
        sf::RectangleShape r2;
        sf::CircleShape r3;
        sg::Component c0;
        sg::Component c1;
        sg::Component c2;
        sg::Component c3;
        void handleCollision(sg::Entity &otherE, const std::vector<sf::Vector2f> &collisionVs) {

            sg::Entity::handleCollision(otherE, collisionVs);
            if (this->r0.getFillColor() == sf::Color::White)
                this->fill(sf::Color::Yellow);
            else if (this->r0.getFillColor() == sf::Color::Yellow)
                this->fill(sf::Color::White);
            else if (this->r0.getFillColor() == sf::Color::Red)
                this->fill(sf::Color::Green);
            else if (this->r0.getFillColor() == sf::Color::Green)
                this->fill(sf::Color::Red);

            if (TestBox *b = dynamic_cast<TestBox *>(&otherE)) { 
                if (b->getFill() == sf::Color::White)
                    b->fill(sf::Color::Yellow);
                else if (b->getFill() == sf::Color::Yellow)
                    b->fill(sf::Color::White);
                else if (b->getFill() == sf::Color::Red)
                    b->fill(sf::Color::Green);
                else if (b->getFill() == sf::Color::Green)
                    b->fill(sf::Color::Red);
            }

        }
    
    public:
        TestBox() :
        sg::Entity()
        {

            r0.setSize(sf::Vector2f(100.0f, 50.0f));
            r0.setOrigin(50.0f, 25.0f);
            c0.d = &r0;
            c0.t = &r0;
            //this->addComponent(c0);
            r1.setRadius(40.0f);
            r1.setOrigin(40.0f, 40.0f);
            r1.move(100.0f, 0.0f);
            r1.scale(2.0f, 1.0f);
            c1.d = &r1;
            c1.t = &r1;
            //this->addComponent(c1);
            r2.setSize(sf::Vector2f(250.0f, 10.0f));
            r2.setOrigin(125.0f, 5.0f);
            r2.rotate(-90.0f);
            c2.d = &r2;
            c2.t = &r2;
            //this->addComponent(c2);
            r3.setRadius(40.0f);
            r3.setOrigin(40.0f, 40.0f);
            r3.move(-100.0f, 0.0f);
            c3.d = &r3;
            c3.t = &r3;
            this->addComponent(c3);

        }
        TestBox(bool isCollidable) :
        sg::Entity(isCollidable)
        {

            r0.setSize(sf::Vector2f(100.0f, 50.0f));
            r0.setOrigin(50.0f, 25.0f);
            c0.d = &r0;
            c0.t = &r0;
            this->addComponent(c0);
            r1.setRadius(40.0f);
            r1.setOrigin(40.0f, 40.0f);
            r1.move(100.0f, 0.0f);
            r1.scale(2.0f, 1.0f);
            c1.d = &r1;
            c1.t = &r1;
            //this->addComponent(c1);
            r2.setSize(sf::Vector2f(250.0f, 10.0f));
            r2.setOrigin(125.0f, 5.0f);
            r2.rotate(-90.0f);
            c2.d = &r2;
            c2.t = &r2;
            //this->addComponent(c2);
            r3.setRadius(40.0f);
            r3.setOrigin(40.0f, 40.0f);
            r3.move(-100.0f, 0.0f);
            c3.d = &r3;
            c3.t = &r3;
            //this->addComponent(c3);

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
