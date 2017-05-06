#pragma once

#include <list>
#include <utility>
#include <functional>

#include <SFML/Graphics.hpp>

namespace sg {

    template<class T>
    class Quadtree {

        private:
            uint64_t MAX_OBJECTS;
            uint64_t MAX_LEVEL;

            uint64_t OBJECTS_OFFSET;
            uint64_t LEVEL_OFFSET;

            uint64_t level;
            std::list<std::pair<const sf::Rect<long>, T>> objects;
            sf::Rect<long> bounds;
            Quadtree *nodes[4];
            Quadtree *parent;

            void split();
            void merge();
            long getIndex(const sf::Rect<long> &) const;
            void distributeObjects();

        public:
            Quadtree();
            Quadtree(uint64_t, uint64_t, uint64_t, const sf::Rect<long> &);
            Quadtree(const Quadtree &);
            void operator= (const Quadtree &);
            ~Quadtree();
            void size(uint64_t &) const;
            void init(uint64_t, uint64_t, uint64_t, const sf::Rect<long> &);
            void clear();
            bool containedWithin(const sf::Rect<long> &, const sf::Rect<long> &) const;
            bool boundsOverlap(const sf::Rect<long> &, const sf::Rect<long> &) const;
            void insert(const sf::Rect<long> &, T);
            bool remove(const sf::Rect<long> &, T, std::function<bool(const T obj0, const T obj1)> comp=[](const T obj0, const T obj1)->bool{return obj0 == obj1;});
            //void update(const sf::Rect<long> &, std::function<sf::Rect<long>(const T obj)>);
            void retrieve(std::vector<T> &, const sf::Rect<long> &) const;

    };

}
