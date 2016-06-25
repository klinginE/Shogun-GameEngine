#pragma once

#include <list>
#include <utility>

#include <SFML/Graphics.hpp>

namespace sg {

    template<class T>
    class Quadtree {

        private:
            uint64_t MAX_OBJECTS;
            uint64_t MAX_LEVEL;

            uint64_t level;
            std::list<std::pair<const sf::Rect<long>, T>> objects;
            sf::Rect<long> bounds;
            Quadtree *nodes[4];

            void split();
            long getIndex(const sf::Rect<long> &) const;

        public:
            Quadtree();
            Quadtree(uint64_t, uint64_t, uint64_t, const sf::Rect<long> &);
            ~Quadtree();
            void init(uint64_t, uint64_t, uint64_t, const sf::Rect<long> &);
            void clear();
            void insert(const sf::Rect<long> &, T);
            bool remove(const sf::Rect<long> &, T);
            void retrieve(std::vector<T> &, const sf::Rect<long> &) const;

    };

}
