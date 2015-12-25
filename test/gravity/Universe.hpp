#pragma once

// Standard includes
#include <math.h>
#include <stdio.h>
#include <limits>

// Shogun includes
#include <GameWorld.hpp>

// Local includes
#include "Star.hpp"

#define NUM_STARS (25*25)
#define NUM_STARS_ACROSS (25)
#define GRAV_CONST 0.01f
#define STAR_SPACING 5.0f
#define STAR_SIZE 1.0f

class Universe : public sg::GameWorld {
    
    Star stars[NUM_STARS];
    float disp_radius;

    public:
        Universe() {

            deactivateInput();
            deactivateCollisions();

            for (int i = 0; i < NUM_STARS_ACROSS; i++) {
                for (int j = 0; j < NUM_STARS/NUM_STARS_ACROSS; j++) {
                    stars[i + j*NUM_STARS_ACROSS].move(
                            sf::Vector2f(i*STAR_SPACING,
                                         j*STAR_SPACING));
                    addEntity(dynamic_cast<sg::Entity *>(&stars[i + j*NUM_STARS_ACROSS]));
                }
            }

            disp_radius = 1.0f;
            
        };

        void update(const sf::Time &tslu) {
            sg::GameWorld::update(tslu);
            QuadTree qT;

            // TODO: do quad-tree method instead
            for (int i = 0; i < NUM_STARS; i++) {
                for (int j = 0; j < NUM_STARS; j++) {
                    if (j == i) continue;
                    sf::Vector2f diff = stars[j].getPos() - stars[i].getPos();
                    float dist_squared = diff.x*diff.x + diff.y*diff.y;
                    if (dist_squared > STAR_SIZE) {
                        float dist = sqrt(dist_squared);
                        diff = diff*GRAV_CONST/(dist_squared*dist);
                        stars[i].changeVel(diff);
                    }
                    else {
                        sf::Vector2f vel1 = stars[i].getVel();
                        sf::Vector2f vel2 = stars[j].getVel();
                        sf::Vector2f newVel = (vel1 + vel2)/2.0f;
                        stars[i].setVel(newVel);
                        stars[j].setVel(newVel);
                    }
                }
            }

            for (int i = 0; i < NUM_STARS; i++) {
                stars[i].translate(stars[i].getVel());
                stars[i].setDispRadius(disp_radius);
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
                t->add(&stars[i], minX, minY, maxX, maxY);
                // TODO: have this function return leaf where it added
            }
        };

};
