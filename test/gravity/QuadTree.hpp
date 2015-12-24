#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Local includes
#include "Star.hpp"

// Standard includes
#include <assert.h>

class QuadTree {

    QuadTree *parent;
    QuadTree *child_upleft;
    QuadTree *child_upright;
    QuadTree *child_downleft;
    QuadTree *child_downright;

    sf::Vector2f center_of_mass;
    int numberOfStars;
    Star *star;

    public:
        QuadTree() {
            parent = NULL;
            child_upleft = NULL;
            child_upright = NULL;
            child_downleft = NULL;
            child_downright = NULL;
            star = NULL;
        };
        ~QuadTree() {
            clean();
        };

        void clean() {
            if (child_upleft) child_upleft->clean();
            delete child_upleft;
            if (child_upright) child_upright->clean();
            delete child_upright;
            if (child_downleft) child_downleft->clean();
            delete child_downleft;
            if (child_downright) child_downright->clean();
            delete child_downright;
        };

        void gravity_recursive( // TODO TODO TODO

        void add(Star *newStar, float minX, float minY,
                                float maxX, float maxY,
                 bool __override) {

            if (__override || numberOfStars > 1) {

                sf::Vector2f pos = newStar->getPos();

                center_of_mass = (center_of_mass*numberOfStars + pos)/(numberOfStars + 1);

                float splitX = (minX + maxX)/2;
                float splitY = (minY + maxY)/2;

                if (pos.x < splitX) {
                    if (pos.y < splitY) {
                        // upleft
                        if (this->child_upleft) {
                            this->child_upleft->add(newStar, minX, minY, splitX, splitY);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_upleft = newLeaf;
                            newLeaf->add(newStar, minX, minY, splitX, splitY);
                        }
                    }
                    else { // pos.y >= splitY
                        // downleft
                        if (this->child_downleft) {
                            this->child_downleft->add(newStar, minX, minY, splitX, splitY);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_downleft = newLeaf;
                            newLeaf->add(newStar, minX, splitY, splitX, maxY);
                        }
                    }
                }
                else { // pos.x >= splitX
                    if (pos.y < splitY) {
                        // upright
                        if (this->child_upright) {
                            this->child_upright->add(newStar, splitX, minY, maxX, splitY);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_upright = newLeaf;
                            newLeaf->add(newStar, splitX, minY, maxX, splitY);
                        }
                    }
                    else { // pos.y >= splitY
                        // downright
                        if (this->child_downright) {
                            this->child_downright->add(newStar, splitX, splitY, maxX, maxY);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_downright = newLeaf;
                            newLeaf->add(newStar, splitX, splitY, maxX, maxY);
                        }
                    }
                }
                numberOfStars += 1;
            }
            else if (numberOfStars == 1) {
            
                assert(this->star != NULL);
                
                sf::Vector2f pos = newStar->getPos();

                center_of_mass = (center_of_mass + pos)/2;
                
                Star *otherStar = this->star;
                
                this->numberOfStars = 0;
                this->add(otherStar, minX, minY, maxX, maxY, true);
                this->add(newStar, minX, minY, maxX, maxY, true);
            }
            else {

                star = newStar;
                centerOfMass = newStar->getPos();
                numberOfStars += 1;
            }
        };

        void setParent(QuadTree *newParent) {
            parent = newParent;
        };
        QuadTree *getParent() {
            return parent;
        };

        void setChildUpLeft(QuadTree *childUpLeft) {
            child_upleft = childUpLeft;
        };
        QuadTree *getChildUpLeft() {
            return child_upleft;
        };

        void setChildUpRight(QuadTree *childUpRight) {
            child_upright = childUpRight;
        };
        QuadTree *getChildUpRight() {
            return child_upright;
        };

        void setChildDownLeft(QuadTree *childDownLeft) {
            child_downleft = childDownLeft;
        };
        QuadTree *getChildDownLeft() {
            return child_downleft;
        };

        void setChildDownRight(QuadTree *childDownRight) {
            child_downright = childDownRight;
        };
        QuadTree *getChildUpRight() {
            return child_upright;
        };

        void setStar(Star *newStar) {
            star = newStar;
        };
        Star *getStar() {
            return star;
        };

        void setCenterOfMass(Vector2f newCenterOfMass) {
            center_of_mass = newCenterOfMass;
        };
        Vector2f getCenterOfMass() {
            return center_of_mass;
        };

        void setLevel(int newLevel) {
            level = newLevel;
        };
        int getLevel() {
            return level;
        };

        void setMinX(float newMinX) {
            minX = newMinX;
        };
        void setMinY(float newMinY) {
            minY = newMinY;
        };
        void setMaxX(float newMaxX) {
            maxX = newMaxX;
        };
        void setMaxY(float newMaxY) {
            maxY = newMaxY;
        };
        float getMinX() {
            return minX;
        };
        float getMinY() {
            return minY;
        };
        float getMaxX() {
            return maxX;
        };
        float getMaxY() {
            return maxY;
        };
};
