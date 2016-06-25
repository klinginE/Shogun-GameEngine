#pragma once

#include <limits.h>

#include <Shogun/Management/Quadtree.hpp>

namespace sg {

    template<class T>
    Quadtree<T>::Quadtree() :
    MAX_OBJECTS(1),
    MAX_LEVEL(std::numeric_limits<uint64_t>::max())
    {

        this->level = 0;
        this->bounds = sf::Rect<long>(static_cast<long>(ceil(static_cast<double>(std::numeric_limits<long>::min()) / 2.0)), 
                                      static_cast<long>(ceil(static_cast<double>(std::numeric_limits<long>::min()) / 2.0)),
                                      std::numeric_limits<long>::max(),
                                      std::numeric_limits<long>::max());
        for (uint32_t i = 0; i < 4; ++i)
            this->nodes[i] = NULL;

    }

    template<class T>
    Quadtree<T>::Quadtree(uint64_t maxObj, uint64_t maxLevel, uint64_t pLevel, const sf::Rect<long> &pBounds) :
    MAX_OBJECTS(maxObj),
    MAX_LEVEL(maxLevel)
    {

        this->level = pLevel;
        this->bounds.left = pBounds.left;
        this->bounds.top = pBounds.top;
        this->bounds.width = pBounds.width;
        this->bounds.height = pBounds.height;
        for (uint32_t i = 0; i < 4; ++i)
            this->nodes[i] = NULL;

    }

    template<class T>
    Quadtree<T>::~Quadtree() {

        this->clear();

    }

    template<class T>
    void Quadtree<T>::clear() {

        this->objects.clear();
        for (uint32_t i = 0; i < 4; ++i)
            if (this->nodes[i]) {

                //this->nodes[i].clear(); //[EK]: Not needed?
                                          //[EK]: delete calls clear.
                delete this->nodes[i];
                this->nodes[i] = NULL;

            }

    }

    template<class T>
    void Quadtree<T>::init(uint64_t maxObj, uint64_t maxLevel, uint64_t pLevel, const sf::Rect<long> &pBounds) {

        this->MAX_OBJECTS = maxObj;
        this->MAX_LEVEL = maxLevel;
        this->level = pLevel;
        this->bounds.left = pBounds.left;
        this->bounds.top = pBounds.top;
        this->bounds.width = pBounds.width;
        this->bounds.height = pBounds.height;
        for (uint32_t i = 0; i < 4; ++i)
            this->nodes[i] = NULL;

    }

    template<class T>
    void Quadtree<T>::split() {

        long subWidth = static_cast<long>(static_cast<double>(this->bounds.width) / 2.0);
        long subHeight = static_cast<long>(static_cast<double>(this->bounds.height) / 2.0);
        long x = this->bounds.left;
        long y = this->bounds.top;

        this->nodes[0] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x + subWidth, y, subWidth, subHeight));
        this->nodes[1] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x, y, subWidth, subHeight));
        this->nodes[2] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x, y + subHeight, subWidth, subHeight));
        this->nodes[3] = new Quadtree(this->MAX_OBJECTS, this->MAX_LEVEL, this->level + 1, sf::Rect<long>(x + subWidth, y + subHeight, subWidth, subHeight));

    }

    template<class T>
    long Quadtree<T>::getIndex(const sf::Rect<long> &pRect) const {

        long index = -1;
        double verticalMidpoint = static_cast<double>(this->bounds.left) + (static_cast<double>(this->bounds.width) / 2.0);
        double horizontalMidpoint = static_cast<double>(this->bounds.top) + (static_cast<double>(this->bounds.height) / 2.0);

        bool topQuadrant = (static_cast<double>(pRect.top) < horizontalMidpoint && static_cast<double>(pRect.top + pRect.height) < horizontalMidpoint);
        bool bottomQuadrant = (static_cast<double>(pRect.top) > horizontalMidpoint);

        if (static_cast<double>(pRect.left) < verticalMidpoint && static_cast<double>(pRect.left + pRect.width) < verticalMidpoint) {

            if (topQuadrant)
                index = 1;
            else if (bottomQuadrant)
                index = 2;

        }
        else if (static_cast<double>(pRect.left) > verticalMidpoint) {

            if (topQuadrant)
                index = 0;
            else if (bottomQuadrant)
                index = 3;

        }

        return index;

    }

    template<class T>
    void Quadtree<T>::insert(const sf::Rect<long> &pRect, T obj) {

        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1) {

                this->nodes[index]->insert(pRect, obj);
                return;

            }

        }

        this->objects.push_back(std::make_pair(pRect, obj));
        if (this->objects.size() > this->MAX_OBJECTS && this->level < this->MAX_LEVEL) {

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
    bool Quadtree<T>::remove(const sf::Rect<long> &pRect, T obj) {

        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1) {

                if (this->nodes[index]->remove(pRect, obj))
                    return true;

            }

        }

        for (auto it = this->objects.begin(); it != this->objects.end(); ++it)
            if (it->second == obj) {

                it = this->objects.erase(it);
                return true;

            }

        return false;

    }

    template<class T>
    void Quadtree<T>::retrieve(std::vector<T> &returnObjects, const sf::Rect<long> &pRect) const {

        if (this->nodes[0]) {

            long index = this->getIndex(pRect);
            if (index != -1)
                this->nodes[index]->retrieve(returnObjects, pRect);
            else
                for (uint32_t i = 0; i < 4; ++i)
                    this->nodes[i]->retrieve(returnObjects, pRect);

        }

        for (auto &p : this->objects)
            returnObjects.push_back(p.second);

    }

}
