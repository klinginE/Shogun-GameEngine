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

#define RADIUS_MODIFIER 100.0f
#define SPEED_MODIFIER 100.0f

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
            circleShape.setOrigin(getRadius(), getRadius());
            addDrawable(circleShape);
        };

        void update(sf::Time t) {

            sg::Entity::update(t);

            if (myWindow)
                myWindow->setPosInWorld(this->getPosition());
        };

        void setMyWindow(sg::GameWindow &newWindow) {
            myWindow = &newWindow;
        };
        
        float getMass() {
            return mass;
        };

        void setMass(float newMass) {
            mass = newMass;
            circleShape.setRadius(getRadius());
        };

        float getSpeed() {
            return SPEED_MODIFIER/getMass();
        };

        float getRadius() {
            return (float) sqrt(mass/M_PI) * RADIUS_MODIFIER;
        };

        void moveLeft(sf::Time t) {
            this->move(sf::Vector2f(-getSpeed()*t.asSeconds(), 0));
        };
        void moveRight(sf::Time t) {
            this->move(sf::Vector2f(getSpeed()*t.asSeconds(), 0));
        };
        void moveUp(sf::Time t) {
            this->move(sf::Vector2f(0, -getSpeed()*t.asSeconds()));
        };
        void moveDown(sf::Time t) {
            this->move(sf::Vector2f(0, getSpeed()*t.asSeconds()));
        };

};
