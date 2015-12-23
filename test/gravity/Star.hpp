#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Shogun includes
#include <Entity.hpp>
#include <GameLoop.hpp>

// standard includes
#include <cstdlib>

#define STAR_RADIUS 1

class Star : public sg::Entity {
    
    sf::Sprite sprite;
    sf::Vector2f vel;

    public:
        Star() : sg::Entity() {
            sprite.setTextureRect(sf::IntRect(0, 0, STAR_RADIUS*2, STAR_RADIUS*2));
            addSprite(sprite);

            float xVel = ((float) (std::rand() % 10)) / 100.0f;
            float yVel = ((float) (std::rand() % 10)) / 100.0f;
            if (std::rand() % 2) xVel = -xVel;
            if (std::rand() % 2) yVel = -yVel;

            setVel(sf::Vector2f(xVel, yVel));
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

        void draw() {
            
            // Move view to draw entity in the correct place
            sf::View saveView = sg::GameLoop::inst().getRenderWindow().getView();
            sf::View drawView = saveView;
            drawView.setCenter(saveView.getCenter().x - getPos().x,
                               saveView.getCenter().y - getPos().y);
            sg::GameLoop::inst().getRenderWindow().setView(drawView);

            // Draw circle
            sf::CircleShape circle;
            circle.setRadius(STAR_RADIUS);
            circle.setFillColor(sf::Color(255, 255, 255, 100));
            sg::GameLoop::inst().getRenderWindow().draw(circle);

            // Set view back to the way it was before
            sg::GameLoop::inst().getRenderWindow().setView(saveView);

        };
};
