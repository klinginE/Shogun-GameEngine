#pragma once

// Standard includes
#include <math.h>
#include <stdio.h>
#include <limits>

// Shogun includes
#include <GameWorld.hpp>

#define GRAV_CONST 1.0f
#define NUM_STARS (50*50)
#define NUM_STARS_ACROSS (50)
#define STAR_SPACING 90.0f

// Local includes
#include "Star.hpp"
#include "QuadTree.hpp"

class Universe : public sg::GameWorld {
    
    Star stars[NUM_STARS];
    float disp_radius;

    sg::BoundingShape boundingShape;
    sg::BoundedSprite boundedSprite;
    sf::CircleShape circleShape;

    public:
        Universe() {

            deactivateInput();
            activateCollisions();
            
            circleShape.setRadius(STAR_SIZE);
            boundingShape.addShape(circleShape);
            boundedSprite.setSurface(boundingShape);
            boundedSprite.setPosition(sf::Vector2f(-STAR_SIZE, -STAR_SIZE));

            for (int i = 0; i < NUM_STARS; i++) {
                int x_i = i % NUM_STARS_ACROSS;
                int y_i = i / NUM_STARS_ACROSS;
                stars[i].move(sf::Vector2f(x_i*STAR_SPACING,
                                           y_i*STAR_SPACING));
                stars[i].addSprite(boundedSprite);
                addEntity(dynamic_cast<sg::Entity *>(&stars[i]));
            }

            disp_radius = 1.0f;
            
        };

        void update(const sf::Time &tslu) {
            QuadTree qT;

            createQuadTree(&qT);

            qT.gravity();
            for (int i = 0; i < NUM_STARS; i++) {
                stars[i].translate(stars[i].getVel());
                stars[i].setDispRadius(disp_radius);
            }

            qT.clean();

            // process input
            if (inputActive && inputManager)
                inputManager->processInput();
            // Detect and resolve collisions between entities
            if (collisionActive)
                scanline();
            // update all entities
            for (auto entityIter = entities.begin();
                 entityIter != entities.end(); ++entityIter) {
                sg::Entity *e = *entityIter;
                e->update(tslu);
            }

        };

        void setDispRadius(float newDispRadius) {
            disp_radius = newDispRadius;
        };

    private:
        void createQuadTree(QuadTree *t) {
            float minX = std::numeric_limits<float>::max();
            float minY = std::numeric_limits<float>::max();
            float maxX = -std::numeric_limits<float>::max();
            float maxY = -std::numeric_limits<float>::max();
            
            for (int i = 0; i < NUM_STARS; i++) {
                sf::Vector2f pos = stars[i].getPos();
                if (pos.x < minX) minX = pos.x;
                if (pos.y < minY) minY = pos.y;
                if (pos.x > maxX) maxX = pos.x;
                if (pos.y > maxY) maxY = pos.y;
            }
            if (maxX - minX > maxY - minY) {
                float medY = (maxY + minY)/2;
                float half_diff = (maxX - minX)/2;
                maxY = medY + half_diff;
                minY = medY - half_diff;
            }

            for (int i = 0; i < NUM_STARS; i++) {
                t->add(&stars[i], minX, minY, maxX, maxY, false);
            }
        };

};
