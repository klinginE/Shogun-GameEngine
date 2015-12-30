#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Local includes
#include "Star.hpp"

// Standard includes
#include <assert.h>
#include <list>

class QuadTree {

    QuadTree *parent;
    QuadTree *child_upleft;
    QuadTree *child_upright;
    QuadTree *child_downleft;
    QuadTree *child_downright;

    sf::Vector2f center_of_mass;
    int numberOfStars;
    Star *star;
    float mass;

    public:
        QuadTree() {
            parent = NULL;
            child_upleft = NULL;
            child_upright = NULL;
            child_downleft = NULL;
            child_downright = NULL;
            star = NULL;
            numberOfStars = 0;
        };
        ~QuadTree() {
            clean();
        };

        void clean() {
            if (child_upleft) {
                QuadTree *delNode = child_upleft;
                child_upleft = NULL;
                delNode->clean();
                delete delNode;
            }
            if (child_upright) {
                QuadTree *delNode = child_upright;
                child_upright = NULL;
                delNode->clean();
                delete delNode;
            }
            if (child_downleft) {
                QuadTree *delNode = child_downleft;
                child_downleft = NULL;
                delNode->clean();
                delete delNode;
            }
            if (child_downright) {
                QuadTree *delNode = child_downright;
                child_downright = NULL;
                delNode->clean();
                delete delNode;
            }
        };

        void gravity() {
            std::list<int> grav_stack;
            std::list<sf::Vector2f> com_stack;
            gravity_recursive(&grav_stack, &com_stack);
        }

        void gravity_recursive(std::list<int> *grav_stack,
                               std::list<sf::Vector2f> *com_stack) {
            if (star == NULL) {
                if (child_upleft) {
                    if (child_upright) {
                        grav_stack->push_back(child_upright->mass);
                        com_stack->push_back(child_upright->center_of_mass);
                    }
                    if (child_downleft) {
                        grav_stack->push_back(child_downleft->mass);
                        com_stack->push_back(child_downleft->center_of_mass);
                    }
                    if (child_downright) {
                        grav_stack->push_back(child_downright->mass);
                        com_stack->push_back(child_downright->center_of_mass);
                    }
                    child_upleft->gravity_recursive(grav_stack, com_stack);
                    if (child_upright) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_downleft) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_downright) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                }
                if (child_upright) {
                    if (child_upleft) {
                        grav_stack->push_back(child_upleft->mass);
                        com_stack->push_back(child_upleft->center_of_mass);
                    }
                    if (child_downleft) {
                        grav_stack->push_back(child_downleft->mass);
                        com_stack->push_back(child_downleft->center_of_mass);
                    }
                    if (child_downright) {
                        grav_stack->push_back(child_downright->mass);
                        com_stack->push_back(child_downright->center_of_mass);
                    }
                    child_upright->gravity_recursive(grav_stack, com_stack);
                    if (child_upleft) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_downleft) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_downright) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                }
                if (child_downleft) {
                    if (child_upright) {
                        grav_stack->push_back(child_upright->mass);
                        com_stack->push_back(child_upright->center_of_mass);
                    }
                    if (child_upleft) {
                        grav_stack->push_back(child_upleft->mass);
                        com_stack->push_back(child_upleft->center_of_mass);
                    }
                    if (child_downright) {
                        grav_stack->push_back(child_downright->mass);
                        com_stack->push_back(child_downright->center_of_mass);
                    }
                    child_downleft->gravity_recursive(grav_stack, com_stack);
                    if (child_upright) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_upleft) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_downright) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                }
                if (child_downright) {
                    if (child_upright) {
                        grav_stack->push_back(child_upright->mass);
                        com_stack->push_back(child_upright->center_of_mass);
                    }
                    if (child_upleft) {
                        grav_stack->push_back(child_upleft->mass);
                        com_stack->push_back(child_upleft->center_of_mass);
                    }
                    if (child_downleft) {
                        grav_stack->push_back(child_downleft->mass);
                        com_stack->push_back(child_downleft->center_of_mass);
                    }
                    child_downright->gravity_recursive(grav_stack, com_stack);
                    if (child_upright) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_upleft) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                    if (child_downleft) {
                        grav_stack->pop_back();
                        com_stack->pop_back();
                    }
                }
            }
            else {
                auto grav_iter = grav_stack->begin();
                auto com_iter = com_stack->begin();

                do {
                    sf::Vector2f diff = *(com_iter) - this->star->getPos();
                    float dist_squared = diff.x*diff.x + diff.y*diff.y;
                    if (dist_squared > this->star->getRadius()) {
                        float dist = sqrt(dist_squared);
                        diff = diff*GRAV_CONST
                             *(this->star->getMass() + (*grav_iter))/(dist_squared*dist*this->star->getMass());
                        this->star->changeVel(diff);
                    }
                }
                while (++grav_iter != grav_stack->end()
                    && ++com_iter != com_stack->end());
            }
        };

        void add(Star *newStar, float minX, float minY,
                                float maxX, float maxY,
                 bool __override) {

            if (__override || numberOfStars > 1) {

                sf::Vector2f pos = newStar->getPos();

                center_of_mass = (center_of_mass*mass + pos*newStar->getMass())/((float) (mass + newStar->getMass()));

                float splitX = (minX + maxX)/2;
                float splitY = (minY + maxY)/2;

                if (pos.x < splitX) {
                    if (pos.y < splitY) {
                        // upleft
                        if (this->child_upleft) {
                            this->child_upleft->add(newStar, minX, minY, splitX, splitY, false);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_upleft = newLeaf;
                            newLeaf->add(newStar, minX, minY, splitX, splitY, false);
                        }
                    }
                    else { // pos.y >= splitY
                        // downleft
                        if (this->child_downleft) {
                            this->child_downleft->add(newStar, minX, splitY, splitX, maxY, false);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_downleft = newLeaf;
                            newLeaf->add(newStar, minX, splitY, splitX, maxY, false);
                        }
                    }
                }
                else { // pos.x >= splitX
                    if (pos.y < splitY) {
                        // upright
                        if (this->child_upright) {
                            this->child_upright->add(newStar, splitX, minY, maxX, splitY, false);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_upright = newLeaf;
                            newLeaf->add(newStar, splitX, minY, maxX, splitY, false);
                        }
                    }
                    else { // pos.y >= splitY
                        // downright
                        if (this->child_downright) {
                            this->child_downright->add(newStar, splitX, splitY, maxX, maxY, false);
                        }
                        else {
                            QuadTree *newLeaf = new QuadTree();
                            newLeaf->parent = this;

                            this->child_downright = newLeaf;
                            newLeaf->add(newStar, splitX, splitY, maxX, maxY, false);
                        }
                    }
                }
                mass += newStar->getMass();
                numberOfStars += 1;
            }
            else if (numberOfStars == 1) {
            
                assert(this->star != NULL);
                
                sf::Vector2f pos = newStar->getPos();

                center_of_mass = (center_of_mass*mass + pos*newStar->getMass())/(mass + newStar->getMass());
                
                Star *otherStar = this->star;
                this->star = NULL;
                
                this->numberOfStars = 0;
                this->mass = 0;
                this->add(otherStar, minX, minY, maxX, maxY, true);
                this->add(newStar, minX, minY, maxX, maxY, true);
            }
            else {

                star = newStar;
                center_of_mass = newStar->getPos();
                mass = newStar->getMass();
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
        QuadTree *getChildDownRight() {
            return child_downright;
        };

        void setStar(Star *newStar) {
            star = newStar;
        };
        Star *getStar() {
            return star;
        };

        void setCenterOfMass(sf::Vector2f newCenterOfMass) {
            center_of_mass = newCenterOfMass;
        };
        sf::Vector2f getCenterOfMass() {
            return center_of_mass;
        };

};
