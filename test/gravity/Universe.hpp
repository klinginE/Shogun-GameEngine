#pragma once

// Standard includes
#include <math.h>
#include <stdio.h>
#include <limits>
#include <cstdlib>

// Shogun includes
#include <GameWorld.hpp>

#define GRAV_CONST 500.0f
#define STARS_WIDTH 81
#define STARS_HEIGHT 81
#define NUM_STARS STARS_WIDTH*STARS_HEIGHT

#define TIME_MULTIPLIER 0.01f
#define GRAVITY_SMOOTHING 10000.0f

#define RING_WIDTH (100.0f)
#define RING_START (30.0f)

#define ALPHA 0.5f

#define MIN_DISP_RADIUS_RATIO 0.0015f
#define START_MASS 1.0f
#define RADIUS_MODIFIER 1.0f
#define INITIAL_ZOOM (1.0f/1.0f)

#define INITIAL_VELOCITY 300.0f
#define INITIAL_VELOCITY_ON (1)

#define STAR_SPACING 10.0f

// Local includes
#include "Star.hpp"
#include "QuadTree.hpp"

class Universe : public sg::GameWorld {
    
    Star stars[NUM_STARS];
    float min_disp_radius;

    public:
        Universe() {

            deactivateInput();
            deactivateCollisions();
            
            sf::Vector2f centerPos(0, 0);
            
            for (int i = 0; i < STARS_WIDTH; i++) {
                for (int j = 0; j < STARS_HEIGHT; j++) {
                    
                    sf::Vector2f pos(i*STAR_SPACING - STARS_WIDTH*STAR_SPACING/2.0f, j*STAR_SPACING - STARS_HEIGHT*STAR_SPACING/2.0f);

                    stars[j + i*STARS_HEIGHT].move(pos);

                    addEntity(dynamic_cast<sg::Entity *>(&stars[i*STARS_HEIGHT+j]));
                }
            }

            min_disp_radius = 1.0f;
            
            update(sf::seconds(1));
        };

        void update(const sf::Time &tslu) {

            QuadTree qT;

            createQuadTree(&qT);

            qT.gravity();
            for (int i = 0; i < NUM_STARS; i++) {
                stars[i].move(stars[i].getVel()*((float) tslu.asMilliseconds())*TIME_MULTIPLIER);
                stars[i].setMinDispRadius(min_disp_radius);
            }

            qT.clean();

            GameWorld::update(tslu*TIME_MULTIPLIER);
        };

        void setMinDispRadius(float newDispRadius) {
            min_disp_radius = newDispRadius;
        };

    private:
        void createQuadTree(QuadTree *t) {
            float minX = std::numeric_limits<float>::max();
            float minY = std::numeric_limits<float>::max();
            float maxX = -std::numeric_limits<float>::max();
            float maxY = -std::numeric_limits<float>::max();
            
            for (int i = 0; i < NUM_STARS; i++) {
                if (stars[i].getDeletionStatus())
                    continue;

                sf::Vector2f pos = stars[i].getPosition();
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
                if (stars[i].getDeletionStatus())
                    continue;
                
                t->add(&stars[i], minX, minY, maxX, maxY, false);
            }
        };

};
