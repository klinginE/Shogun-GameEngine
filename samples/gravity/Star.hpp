#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Shogun includes
#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Elements/BoundingShape.hpp>

// standard includes
#include <cstdlib>
#include <math.h>
#include <stdio.h>

#include "Universe.hpp"

class Star : public sg::Entity {
    
    sf::Sprite sprite;
    sf::Vector2f vel;
    float min_disp_radius;
    float mass;
    sf::CircleShape circleShape = sf::CircleShape();

    public:
        Star() : sg::Entity() {
            
            min_disp_radius = 1.0f;
            mass = START_MASS;
            setIsCollidable(true);

            circleShape.setRadius(getRadius());
            circleShape.setFillColor(sf::Color::Yellow);
            circleShape.setOrigin(getRadius(), getRadius());
            this->addDrawable(circleShape);

        };

        float getMass() const {
            return mass;
        };
        void setMass(float newMass) {
            mass = newMass;
            circleShape.setRadius(getRadius());
        };

        float getRadius() {
            return (float) sqrt(mass/M_PI) * RADIUS_MODIFIER;
        };

        void setVel(sf::Vector2f newVel) {
            vel = newVel;
        };
        sf::Vector2f getVel() const {
            return vel;
        };
        void changeVel(sf::Vector2f deltaVel) {
            vel.x += deltaVel.x;
            vel.y += deltaVel.y;
        };

        void setMinDispRadius(float newRadius) {
            min_disp_radius = newRadius;
        };

        void update(sf::Time tslu) {

            sf::View view = sg::GameLoop::inst().getRenderWindow().getView();
            sf::Vector2f viewSize = view.getSize();

            float viewsize_threshold = 500.0f;

            if (viewSize.x > viewsize_threshold) {

                float sizeRatio = viewsize_threshold/viewSize.x;
                this->setScale(sf::Vector2f(1.0f/sizeRatio, 1.0f/sizeRatio));

            }
            else
                this->setScale(sf::Vector2f(1.0f, 1.0f));

            sg::Entity::update(tslu);

        }
        
        void handleCollision(Entity &e, const std::map<std::pair<uint64_t, uint64_t>, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f>> &colInfo) {

            return;
            if (getDeletionStatus())
                return;

            Star *other = dynamic_cast<Star *>(&e);
            if (other && other->getMass() <= this->getMass()) {

                sf::Vector2f thisVel = this->getVel();
                float thisMass = this->getMass();
                sf::Vector2f otherVel = other->getVel();
                float otherMass = other->getMass();
                sf::Vector2f avgVel = (thisVel*thisMass + otherVel*otherMass)/(thisMass + otherMass);
                this->setVel(avgVel);
                sf::Vector2f avgPos = (this->getPosition()*thisMass + other->getPosition()*otherMass)/(thisMass + otherMass);
                this->setPosition(avgPos);
                this->setMass(thisMass + otherMass);
                other->setDeletionStatus(true);

            }
            else if (other && other->getMass() > this->getMass()) {

                sf::Vector2f thisVel = this->getVel();
                float thisMass = this->getMass();
                sf::Vector2f otherVel = other->getVel();
                float otherMass = other->getMass();
                sf::Vector2f avgVel = (thisVel*thisMass + otherVel*otherMass)/(thisMass + otherMass);
                other->setVel(avgVel);
                sf::Vector2f avgPos = (this->getPosition()*thisMass + other->getPosition()*otherMass)/(thisMass + otherMass);
                other->setPosition(avgPos);
                other->setMass(thisMass + otherMass);
                this->setDeletionStatus(true);

            }

        };

};

