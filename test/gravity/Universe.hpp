#pragma once

// Standard includes
#include <math.h>
#include <stdio.h>
#include <limits>
#include <cstdlib>

// Shogun includes
#include <GameWorld.hpp>

#define GRAV_CONST 0.3f
//#define GRAV_CONST 1.0f
#define NUM_STARS 81*100
#define NUM_STARS_ACROSS 100
//#define NUM_STARS 5000
//#define NUM_STARS_ACROSS 5000
#define STAR_SPACING 50.0f

#define UNIVERSE_WIDTH 1200
#define UNIVERSE_HEIGHT 1200

// Local includes
#include "Star.hpp"
#include "QuadTree.hpp"

class Universe : public sg::GameWorld {
    
    Star stars[NUM_STARS];
    float min_disp_radius;

    public:
        Universe() {

            deactivateInput();
            activateCollisions();
            

            for (int i = 0; i < NUM_STARS; i++) {
                float x = ((float) std::rand()) / (((float) RAND_MAX)/UNIVERSE_WIDTH);
                float y = ((float) std::rand()) / (((float) RAND_MAX)/UNIVERSE_HEIGHT);
                stars[i].move(sf::Vector2f(x, y));
                addEntity(dynamic_cast<sg::Entity *>(&stars[i]));
            }

            min_disp_radius = 1.0f;
            
            update(sf::seconds(1));
        };

        void update(const sf::Time &tslu) {
            QuadTree qT;

            createQuadTree(&qT);

            qT.gravity();
            for (int i = 0; i < NUM_STARS; i++) {
                stars[i].translate(stars[i].getVel());
                stars[i].setMinDispRadius(min_disp_radius);
            }

            qT.clean();

            GameWorld::update(tslu);
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
                if (stars[i].getDeletionStatus())
                    continue;
                
                t->add(&stars[i], minX, minY, maxX, maxY, false);
            }
        };

};
