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

#define STAR_SIZE 2.0f

class Star : public sg::Entity {
    
    sf::Sprite sprite;
    sf::Vector2f vel;
    float disp_radius;
//    static sg::BoundingShape boundingShape;
//    static sg::BoundedSprite boundedSprite;
//    static sf::CircleShape circleShape;

    public:
        Star() : sg::Entity() {
            

            float xVel = ((float) (std::rand() % 10)) / 100.0f;
            float yVel = ((float) (std::rand() % 10)) / 100.0f;
            if (std::rand() % 2) xVel = -xVel;
            if (std::rand() % 2) yVel = -yVel;

            setVel(sf::Vector2f(xVel, yVel));

            disp_radius = 1.0f;
            setIsCollidable(true);
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

        void setDispRadius(float newRadius) {
            disp_radius = newRadius;
        };

        void draw() {
            
            // Move view to draw entity in the correct place
            sf::View saveView = sg::GameLoop::inst().getRenderWindow().getView();
            sf::View drawView = saveView;
            drawView.setCenter(saveView.getCenter().x - getPos().x,
                               saveView.getCenter().y - getPos().y);
            sg::GameLoop::inst().getRenderWindow().setView(drawView);

            // Draw circle
            sf::CircleShape circle;
            circle.setRadius(disp_radius);
            circle.setFillColor(sf::Color(255, 255, 255, 100));
            sg::GameLoop::inst().getRenderWindow().draw(circle);

            // Set view back to the way it was before
            sg::GameLoop::inst().getRenderWindow().setView(saveView);

        };

        // TODO: This function is temporarily made virtual in base class
        /*
        bool collides(sg::Entity &e) {
            Star *other = dynamic_cast<Star *>(&e);
            sf::Vector2f thisPos = this->getPos();
            sf::Vector2f otherPos = other->getPos();
            sf::Vector2f diff = otherPos - thisPos;
            float dist = sqrt(diff.x*diff.x + diff.y*diff.y);
            if (dist < 2*STAR_SIZE) {
                sf::Vector2f thisVel = this->getVel();
                sf::Vector2f otherVel = other->getVel();
                sf::Vector2f avgVel = (thisVel + otherVel)/2.0f;
                this->setVel(avgVel);
                other->setVel(avgVel);
                return true;
            }
            return false;
        };
        */
};
