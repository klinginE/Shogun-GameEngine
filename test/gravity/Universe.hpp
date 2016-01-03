#pragma once

// Standard includes
#include <math.h>
#include <stdio.h>
#include <limits>
#include <cstdlib>

// Shogun includes
#include <GameWorld.hpp>

#define GRAV_CONST 0.01f
//#define GRAV_CONST 1.0f
#define NUM_STARS 80*100
//#define NUM_STARS_ACROSS 100
//#define NUM_STARS 5000
//#define NUM_STARS_ACROSS 5000
//#define STAR_SPACING 500.0f

//#define UNIVERSE_WIDTH 3000
//#define UNIVERSE_HEIGHT 3000

#define TIME_MULTIPLIER 1.0f
#define GRAVITY_SMOOTHING 10000.0f

#define RING_WIDTH (500.0f)
#define RING_START (10.0f)

#define ALPHA 0.5f

#define MIN_DISP_RADIUS_RATIO 0.0015f
#define START_MASS 1.0f
#define RADIUS_MODIFIER 0.2f
#define INITIAL_ZOOM (10.0f/1.0f)

#define INITIAL_VELOCITY 1.0f
#define INITIAL_VELOCITY_ON (0)

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
            
            //sf::Vector2f centerPos(UNIVERSE_WIDTH/2.0f, UNIVERSE_HEIGHT/2.0f);
            sf::Vector2f centerPos(0, 0);
            
//            stars[0].move(centerPos);
//            stars[0].setMass(100.0f);
//            addEntity(dynamic_cast<sg::Entity *>(&stars[0]));
            for (int i = 0; i < NUM_STARS; i++) {

                // random position
                float ang = ((float) std::rand()) / (((float) RAND_MAX)/(2.0f*M_PI));
                float dist = ((float) std::rand()) / (((float) RAND_MAX)/RING_WIDTH);
                dist += RING_START;
                sf::Vector2f pos((float) dist*cos(ang), (float) dist*sin(ang));
                stars[i].move(pos);

                // Random velocity
                sf::Vector2f distVec = pos - centerPos;
                sf::Vector2f vel(-distVec.y, distVec.x);
                vel /= dist;
                vel *= ((float) std::rand()) / (((float) RAND_MAX)/(INITIAL_VELOCITY/dist));
                if (INITIAL_VELOCITY_ON)
                    stars[i].setVel(vel);

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
                stars[i].translate(stars[i].getVel()*((float) tslu.asMilliseconds())*TIME_MULTIPLIER);
                stars[i].setMinDispRadius(min_disp_radius);
            }

            qT.clean();

            //GameWorld::update(tslu*TIME_MULTIPLIER);
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
