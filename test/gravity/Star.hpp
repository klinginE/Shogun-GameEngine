#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Shogun includes
#include <Entity.hpp>
#include <GameLoop.hpp>
#include <BoundingShape.hpp>
#include <BoundedSprite.hpp>

// standard includes
#include <cstdlib>
#include <math.h>
#include <stdio.h>

class Star : public sg::Entity {
    
    sf::Sprite sprite;
    sf::Vector2f vel;
    float min_disp_radius;
    float mass;
    sg::BoundingShape boundingShape;
    sg::BoundedSprite boundedSprite;
    sf::CircleShape circleShape;

    public:
        Star() : sg::Entity() {

            min_disp_radius = 1.0f;
            mass = 0.1f;
            setIsCollidable(true);

            circleShape.setRadius(getRadius());
            boundingShape.addShape(circleShape);
            boundedSprite.setSurface(boundingShape);
            boundedSprite.setPosition(sf::Vector2f(-getRadius(), -getRadius()));
            this->addSprite(boundedSprite);
        };

        float getMass() {
            return mass;
        };
        void setMass(float newMass) {
            mass = newMass;
            circleShape.setRadius(getRadius());
            boundedSprite.setPosition(sf::Vector2f(-getRadius(), -getRadius()));
        };

        float getRadius() {
            return (float) sqrt(mass/M_PI);
        };

        void setVel(sf::Vector2f newVel) {
            vel = newVel;
        };
        sf::Vector2f getVel() {
            return vel;
        };
        void changeVel(sf::Vector2f deltaVel) {
            vel.x += deltaVel.x;
            vel.y += deltaVel.y;
        };

        void setMinDispRadius(float newRadius) {
            min_disp_radius = newRadius;
        };

        void draw() {
            
//            if (this->getDeletionStatus())
//                return;
            // Move view to draw entity in the correct place
            sf::View saveView = sg::GameLoop::inst().getRenderWindow().getView();
            sf::View drawView = saveView;
            drawView.setCenter(saveView.getCenter().x - getPos().x,
                               saveView.getCenter().y - getPos().y);
            sg::GameLoop::inst().getRenderWindow().setView(drawView);

            // Draw circle
            float disp_radius = this->getRadius();
            if (disp_radius < min_disp_radius)
                disp_radius = min_disp_radius;
            sf::CircleShape circle;
            circle.setRadius(disp_radius);
            circle.setFillColor(sf::Color(150, 150, 150, 255));
            circle.setPosition(sf::Vector2f(-disp_radius, -disp_radius));
            sg::GameLoop::inst().getRenderWindow().draw(circle);

            // Set view back to the way it was before
            sg::GameLoop::inst().getRenderWindow().setView(saveView);

        };

//        void handleCollision(Entity &e, const std::vector<sf::Vector2f> &colInfo) {
//            Star *other = dynamic_cast<Star *>(&e);
//            sf::Vector2f thisVel = this->getVel();
//            sf::Vector2f otherVel = other->getVel();
//            sf::Vector2f avgVel = (thisVel + otherVel)/2.0f;
//            this->setVel(avgVel);
//            other->setVel(avgVel);
//            
//            sf::Vector2f avgPos = (this->getPos() + other->getPos())/2.0f;
//            sf::Vector2f radiusUnit = other->getPos() - this->getPos();
//            radiusUnit = radiusUnit
//                       * STAR_SIZE
//                       / ((float) sqrt(radiusUnit.x*radiusUnit.x
//                                     + radiusUnit.y*radiusUnit.y));
//
//            this->move(avgPos - radiusUnit);
//            other->move(avgPos + radiusUnit);
//        };
        
        void handleCollision(Entity &e, const std::vector<sf::Vector2f> &colInfo) {

            return;
            
            if (getDeletionStatus())
                return;

            Star *other = dynamic_cast<Star *>(&e);
            sf::Vector2f thisVel = this->getVel();
            float thisMass = this->getMass();
            sf::Vector2f otherVel = other->getVel();
            float otherMass = other->getMass();
            sf::Vector2f avgVel = (thisVel*thisMass + otherVel*otherMass)/(thisMass + otherMass);
            this->setVel(avgVel);
            
            sf::Vector2f avgPos = (this->getPos()*thisMass + other->getPos()*otherMass)/(thisMass + otherMass);
            this->move(avgPos);

            this->setMass(thisMass + otherMass);

            //other->setMass(0.0f);
            other->setDeletionStatus(true);
        };
};
