#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Shogun includes
#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Elements/BoundingShape.hpp>
#include <Shogun/Management/GameWindow.hpp>

// standard includes
#include <cstdlib>
#include <math.h>
#include <stdio.h>

#define RADIUS_MODIFIER 10.0f
#define SPEED_MODIFIER 300.0f

class Ball : public sg::Entity {

    sf::CircleShape circleShape = sf::CircleShape();
    float mass;
    sg::GameWindow *myWindow = NULL;

    public:
        Ball() : sg::Entity() {

            setMass(1.0f);
            addDrawable(circleShape);

        }

        void handleCollision(Entity &other, const std::map<std::pair<uint64_t, uint64_t>, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f>> &_) {

            Ball *otherBall = dynamic_cast<Ball *>(&other);
            if (otherBall) {

                if (this->getMass() > otherBall->getMass()) {
                    this->setMass(this->getMass() + otherBall->getMass());
                }
                else if (this->getMass() < otherBall->getMass()) {
                    this->setDeletionStatus(true);
                }

            }
        }

        void setColor(sf::Color newColor) {
            circleShape.setFillColor(newColor);
        }

        void update(sf::Time t) {

            sg::Entity::update(t);

            if (myWindow)
                myWindow->setPosInWorld(this->getPosition());
        }

        void setMyWindow(sg::GameWindow &newWindow) {
            myWindow = &newWindow;
        }
        
        float getMass() const {
            return mass;
        }

        void setMass(float newMass) {
            mass = newMass;
            circleShape.setRadius(getRadius());
            circleShape.setOrigin(getRadius(), getRadius());
        }

        float getSpeed() {
            return SPEED_MODIFIER/std::sqrt(std::sqrt(getMass()));
        }

        float getRadius() {
            return (float) sqrt(mass/M_PI) * RADIUS_MODIFIER;
        }

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
            this->move(-getSpeed()*t.asSeconds(), 0);
            handleOutsideOfBounds(bounds);
        }
        void moveRight(sf::Time t, sf::RectangleShape bounds) {
            this->move(getSpeed()*t.asSeconds(), 0);
            handleOutsideOfBounds(bounds);
        }
        void moveUp(sf::Time t, sf::RectangleShape bounds) {
            this->move(0, -getSpeed()*t.asSeconds());
            handleOutsideOfBounds(bounds);
        }
        void moveDown(sf::Time t, sf::RectangleShape bounds) {
            this->move(0, getSpeed()*t.asSeconds());
            handleOutsideOfBounds(bounds);
        }

};
