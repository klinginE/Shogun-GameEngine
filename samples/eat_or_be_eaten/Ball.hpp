#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Shogun includes
#include <Entity.hpp>
#include <GameLoop.hpp>
#include <BoundingShape.hpp>

// standard includes
#include <cstdlib>
#include <math.h>
#include <stdio.h>

#define RADIUS_MODIFIER 10.0f
#define SPEED_MODIFIER 200.0f

class Ball : public sg::Entity {

    sf::Sprite sprite;
    sf::CircleShape circleShape = sf::CircleShape();
    float mass;
    sg::GameWindow *myWindow = NULL;

    public:
        Ball() : sg::Entity() {
            setIsCollidable(true);
            setMass(1.0f);
            circleShape.setRadius(getRadius());
            circleShape.setFillColor(sf::Color(std::rand() % 255,
                                               std::rand() % 255,
                                               std::rand() % 255,
                                               255));
            circleShape.setPosition(-getRadius(), -getRadius());
            addDrawable(circleShape);
        };

        void handleCollision(const Entity &other, const std::vector<sf::Vector2f> &_) {

            const Ball *otherBall = dynamic_cast<const Ball *>(&other);
            if (otherBall) {

                if (this->getMass() > otherBall->getMass()) {
                    this->setMass(this->getMass() + otherBall->getMass());
                }
                else if (this->getMass() < otherBall->getMass()) {
                    this->setDeletionStatus(true);
                }
            }
        };

        void setColor(sf::Color newColor) {
            circleShape.setFillColor(newColor);
        };

        void update(sf::Time t) {

            sg::Entity::update(t);

            if (myWindow)
                myWindow->setPosInWorld(this->getPosition());
        };

        void setMyWindow(sg::GameWindow &newWindow) {
            myWindow = &newWindow;
        };
        
        float getMass() const {
            return mass;
        };

        void setMass(float newMass) {
            mass = newMass;
            circleShape.setRadius(getRadius());
            circleShape.setPosition(-getRadius(), -getRadius());
        };

        float getSpeed() {
            return SPEED_MODIFIER/std::sqrt(std::sqrt(getMass()));
        };

        float getRadius() {
            return (float) sqrt(mass/M_PI) * RADIUS_MODIFIER;
        };

        void handleOutsideOfBounds(sf::RectangleShape bounds) {
            if (this->getPosition().x - this->getRadius() < bounds.getPosition().x)
                this->setPosition(bounds.getPosition().x + this->getRadius(),
                                  this->getPosition().y);
            if (this->getPosition().x + this->getRadius() > bounds.getPosition().x + bounds.getSize().x)
                this->setPosition(bounds.getPosition().x + bounds.getSize().x - this->getRadius(),
                                  this->getPosition().y);
            if (this->getPosition().y - this->getRadius() < bounds.getPosition().y)
                this->setPosition(this->getPosition().x,
                                  bounds.getPosition().y + this->getRadius());
            if (this->getPosition().y + this->getRadius() > bounds.getPosition().y + bounds.getSize().y)
                this->setPosition(this->getPosition().x,
                                  bounds.getPosition().y + bounds.getSize().y - this->getRadius());
        }

        void moveLeft(sf::Time t, sf::RectangleShape bounds) {
            this->move(sf::Vector2f(-getSpeed()*t.asSeconds(), 0));
            handleOutsideOfBounds(bounds);
        };
        void moveRight(sf::Time t, sf::RectangleShape bounds) {
            this->move(sf::Vector2f(getSpeed()*t.asSeconds(), 0));
            handleOutsideOfBounds(bounds);
        };
        void moveUp(sf::Time t, sf::RectangleShape bounds) {
            this->move(sf::Vector2f(0, -getSpeed()*t.asSeconds()));
            handleOutsideOfBounds(bounds);
        };
        void moveDown(sf::Time t, sf::RectangleShape bounds) {
            this->move(sf::Vector2f(0, getSpeed()*t.asSeconds()));
            handleOutsideOfBounds(bounds);
        };

};
