#pragma once

// Standard includes
#include <math.h>
#include <stdio.h>

// Shogun includes
#include <GameWorld.hpp>

// Local includes
#include "Star.hpp"

#define NUM_STARS 1000
#define NUM_STARS_ACROSS 100
#define GRAV_CONST 0.002f

class Universe : public sg::GameWorld {
    
    Star stars[NUM_STARS];

    public:
        Universe() {

            deactivateInput();
            deactivateCollisions();

            for (int i = 0; i < NUM_STARS_ACROSS; i++) {
                for (int j = 0; j < NUM_STARS/NUM_STARS_ACROSS; j++) {
                    stars[i + j*NUM_STARS_ACROSS].move(
                            sf::Vector2f(i*STAR_RADIUS*2,
                                         j*STAR_RADIUS*2));
                    addEntity(dynamic_cast<sg::Entity *>(&stars[i + j*NUM_STARS_ACROSS]));
                }
            }
            
        };

        void update(const sf::Time &tslu) {
            sg::GameWorld::update(tslu);

            // TODO: do quad-tree method instead
            for (int i = 0; i < NUM_STARS; i++) {
                for (int j = 0; j < NUM_STARS; j++) {
                    if (j == i) continue;
                    sf::Vector2f diff = stars[j].getPos() - stars[i].getPos();
                    float dist_squared = diff.x*diff.x + diff.y*diff.y;
                    if (dist_squared > 0.01f) {
                        float dist = sqrt(dist_squared);
                        diff = diff*GRAV_CONST/(dist_squared*dist);
                        stars[i].changeVel(diff);
                    }
                }
            }

            for (int i = 0; i < NUM_STARS; i++)
                stars[i].translate(stars[i].getVel());

        };

};
