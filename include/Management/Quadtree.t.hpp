#pragma once

#include <limits.h>
#include <iostream>

#include <Shogun/Management/Quadtree.hpp>

namespace sg {

    template<class T>
    Quadtree<T>::Quadtree() :
    MAX_OBJECTS(1),
    MAX_LEVEL(std::numeric_limits<uint64_t>::max())
    {

        this->OBJECTS_OFFSET = 0;
        this->LEVEL_OFFSET = 0;
        this->level = 0;
        this->bounds = sf::Rect<long>(static_cast<long>(ceil(static_cast<double>(std::numeric_limits<long>::min()) / 2.0)),
                                      static_cast<long>(ceil(static_cast<double>(std::numeric_limits<long>::min()) / 2.0)),
                                      std::numeric_limits<long>::max(),
                                      std::numeric_limits<long>::max());
        for (uint32_t i = 0; i < 4; ++i)
            this->nodes[i] = NULL;
        this->parent = NULL;

    }

    template<class T>
    Quadtree<T>::Quadtree(uint64_t maxObj, uint64_t maxLevel, uint64_t pLevel, const sf::Rect<long> &pBounds) :
    MAX_OBJECTS(maxObj),
    MAX_LEVEL(maxLevel)
    {

        this->OBJECTS_OFFSET = this->MAX_OBJECTS / std::sqrt<uint64_t>(this->MAX_OBJECTS);
        this->LEVEL_OFFSET = (std::numeric_limits<uint64_t>::max() - this->MAX_LEVEL);
        this->LEVEL_OFFSET = this->LEVEL_OFFSET / std::sqrt<uint64_t>(this->LEVEL_OFFSET);
        this->level = pLevel;
        this->bounds.left = pBounds.left;
        this->bounds.top = pBounds.top;
        this->bounds.width = pBounds.width;
        this->bounds.height = pBounds.height;
        for (uint32_t i = 0; i < 4; ++i)
            this->nodes[i] = NULL;
        this->parent = NULL;

    }

    template<class T>
    Quadtree<T>::~Quadtree() {

        this->clear();

    }

    template<class T>
    void Quadtree<T>::size(uint64_t &c) const {

        c += this->objects.size();
        for (uint32_t i = 0; i < 4; ++i)
            if (this->nodes[i])
                nodes[i]->size(c);

    }

    template<class T>
    void Quadtree<T>::clear() {

        this->objects.clear();
        for (uint32_t i = 0; i < 4; ++i)
            if (this->nodes[i]) {

                delete this->nodes[i];
                this->nodes[i] = NULL;

            }

    }

    template<class T>
    void Quadtree<T>::init(uint64_t maxObj, uint64_t maxLevel, uint64_t pLevel, const sf::Rect<long> &pBounds) {

        this->clear();
        this->MAX_OBJECTS = maxObj;
        this->MAX_LEVEL = maxLevel;
        this->OBJECTS_OFFSET = this->MAX_OBJECTS / std::sqrt<uint64_t>(this->MAX_OBJECTS);
        this->LEVEL_OFFSET = (std::numeric_limits<uint64_t>::max() - this->MAX_LEVEL);
        this->LEVEL_OFFSET = this->LEVEL_OFFSET / std::sqrt<uint64_t>(this->LEVEL_OFFSET);
        this->level = pLevel;
        this->bounds.left = pBounds.left;
        this->bounds.top = pBounds.top;
        this->bounds.width = pBounds.width;
        this->bounds.height = pBounds.height;

    }

    template<class T>
    void Quadtree<T>::distributeObjects() {

        //Am I too big?
        if (this->objects.size() > this->MAX_OBJECTS && this->level < this->MAX_LEVEL) {

            //I'm so damn big!
            if (!this->nodes[0])
                this->split();

            auto it = this->objects.begin();
            while (it != this->objects.end()) {

                long index = this->getIndex(it->first);
                if (index != -1) {

                    this->nodes[index]->insert(it->first, it->second);
                    it = this->objects.erase(it);

                }
                else
                    it++;

            }

        }

    }

    template<class T>
    void Quadtree<T>::split() {

        long subWidth = static_cast<long>(static_cast<double>(this->bounds.width) / 2.0);
        long subHeight = static_cast<long>(static_cast<double>(this->bounds.height) / 2.0);
        long x = this->bounds.left;
        long y = this->bounds.top;

        this->nodes[0] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x + subWidth, y, subWidth, subHeight));
        this->nodes[0]->parent = this;
        this->nodes[1] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x, y, subWidth, subHeight));
        this->nodes[1]->parent = this;
        this->nodes[2] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x, y + subHeight, subWidth, subHeight));
        this->nodes[2]->parent = this;
        this->nodes[3] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x + subWidth, y + subHeight, subWidth, subHeight));
        this->nodes[3]->parent = this;

    }

    template<class T>
    void Quadtree<T>::merge() {

        if (!this->nodes[0])
            return;

        for (uint32_t i = 0; i < 4; ++i) {

            this->nodes[i]->merge();
            this->objects.insert(this->objects.end(), this->nodes[i]->objects.begin(), this->nodes[i]->objects.end());
            this->nodes[i]->clear();
            delete this->nodes[i];
            this->nodes[i] = NULL;

        }
        //We might have taken on too much so lets see if we need to redistribute our objects
        this->distributeObjects();

    }

    template<class T>
    bool Quadtree<T>::containedWithin(const sf::Rect<long> &bound0, const sf::Rect<long> &bound1) const {

        //Is bounds0 contained within or equal to bounds1
        return (bound0.left >= bound1.left) &&
               ((bound0.left + bound0.width) <= (bound1.left + bound1.width)) &&
               (bound0.top >= bound1.top) &&
               ((bound0.top + bound0.height) <= (bound1.top + bound1.height));

    }

    template<class T>
    bool Quadtree<T>::boundsOverlap(const sf::Rect<long> &bound0, const sf::Rect<long> &bound1) const {

        return (bound0.left <= (bound1.left + bound1.width)) &&
               (bound0.top <= (bound1.top + bound1.height)) &&
               ((bound0.left + bound0.width) >= bound1.left) &&
               ((bound0.top + bound0.height) >= bound1.top);

    }

    template<class T>
    long Quadtree<T>::getIndex(const sf::Rect<long> &pRect) const {

        long index = -1;
        double verticalMidpoint = static_cast<double>(this->bounds.left) + (static_cast<double>(this->bounds.width) / 2.0);
        double horizontalMidpoint = static_cast<double>(this->bounds.top) + (static_cast<double>(this->bounds.height) / 2.0);

        bool topQuadrant = (static_cast<double>(pRect.top) <= horizontalMidpoint && static_cast<double>(pRect.top + pRect.height) <= horizontalMidpoint);
        bool bottomQuadrant = (static_cast<double>(pRect.top) > horizontalMidpoint && static_cast<double>(pRect.top + pRect.height) > horizontalMidpoint);

        if (static_cast<double>(pRect.left) <= verticalMidpoint && static_cast<double>(pRect.left + pRect.width) <= verticalMidpoint) {

            if (topQuadrant)
                index = 1;
            else if (bottomQuadrant)
                index = 2;

        }
        else if (static_cast<double>(pRect.left) > verticalMidpoint && static_cast<double>(pRect.left + pRect.width) > verticalMidpoint) {

            if (topQuadrant)
                index = 0;
            else if (bottomQuadrant)
                index = 3;

        }

        return index;

    }

    template<class T>
    void Quadtree<T>::insert(const sf::Rect<long> &pRect, T obj) {

        //Dose the object belong to a sibling or parent?
        if (this->parent && !this->containedWithin(pRect, this->bounds)) {

            //Parent exists and pRect does not go into us, so send obj up the tree
            std::cout << "INSERT: parent" << std::endl;
            this->parent->insert(pRect, obj);
            return;

        }

        //pRect is somewhere other than here so we have to ignore it
        if (!this->containedWithin(pRect, this->bounds))
        {
            std::cout << "INSERT: droping on floor" << std::endl;
            return;
        }

        //Does the object belong to one of my children?
        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1) {

                //We have children and pRect fits in the one at index send it to them
                this->nodes[index]->insert(pRect, obj);
                return;

            }

        }

        //Must belong to me!
        this->objects.push_back(std::make_pair(pRect, obj));
        this->distributeObjects();

    }

    template<class T>
    bool Quadtree<T>::remove(const sf::Rect<long> &pRect, T obj, std::function<bool(const T obj0, const T obj1)> comp) {

        //Its not here if pRect is not overlapping with our bounds
        if (!this->containedWithin(pRect, this->bounds))
            return false;

        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1) {

                if (this->nodes[index]->remove(pRect, obj, comp)) {

                    uint64_t numObjs;
                    this->size(numObjs);
                    //If we are not too out of wak then lets not merge just yet
                    if (numObjs <= (this->MAX_OBJECTS - this->OBJECTS_OFFSET) ||
                        this->level >= (this->MAX_LEVEL + this->LEVEL_OFFSET))
                        this->merge();
                    return true;
                }

            }

        }

        for (auto it = this->objects.begin(); it != this->objects.end(); ++it)
            if (comp(it->second, obj)) {

                it = this->objects.erase(it);
                uint64_t numObjs;
                this->size(numObjs);
                //If we are not too out of wak then lets not merge just yet
                if (numObjs <= (this->MAX_OBJECTS - this->OBJECTS_OFFSET) ||
                    this->level >= (this->MAX_LEVEL + this->LEVEL_OFFSET))
                    this->merge();
                return true;

            }

        return false;

    }
    
    template<class T>
    void Quadtree<T>::update(const sf::Rect<long> &pRect, std::function<sf::Rect<long>(const T obj)> getBounds) {

        //std::cout << "UPDATING" << std::endl;
        if (!this->containedWithin(pRect, this->bounds)) {
            std::cout << "UPDATING: bounds don't overlap" << std::endl;
            return;
        }

        //std::cout << "BOUNDS a"
        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1)
                this->nodes[index]->update(pRect, getBounds);
            else
                for (uint32_t i = 0; i < 4; ++i)
                    this->nodes[i]->update(pRect, getBounds);

        }

        std::list<std::pair<const sf::Rect<long>, T>> objectsCpy;
        objectsCpy.insert(objectsCpy.end(), this->objects.begin(), this->objects.end());
        this->objects.clear();
        for (auto &p : objectsCpy)
            this->insert(getBounds(p.second), p.second);

    }

    template<class T>
    void Quadtree<T>::retrieve(std::vector<T> &returnObjects, const sf::Rect<long> &pRect) const {

        if (!this->boundsOverlap(pRect, this->bounds))
            return;

        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1)
                this->nodes[index]->retrieve(returnObjects, pRect);
            else
                for (uint32_t i = 0; i < 4; ++i)
                    this->nodes[i]->retrieve(returnObjects, pRect);

        }

        for (auto &p : this->objects)
            if (this->boundsOverlap(p.first, pRect))
                returnObjects.push_back(p.second);

    }

}
