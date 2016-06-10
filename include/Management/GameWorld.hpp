#pragma once

//C++ Includes
#include <map>
#include <vector>
#include <functional>

//SFML Includes
#include <SFML/Graphics.hpp>

//Shogun Includes
#include <Shogun/Elements/Entity.hpp>

namespace sg {

    enum scanline_t : bool {
        VERTICAL,
        HORIZONTAL
    };
    
    class GameWorld {

        protected:
            std::map<uint32_t, std::vector<Entity *>> entities;
            scanline_t scanlineType;
            bool collisionActive;

        public:
            GameWorld();
            GameWorld(std::map<uint32_t, std::vector<Entity *>>);
            virtual ~GameWorld() {}

            virtual void update(const sf::Time &);

            void addEntity(uint32_t, Entity &entity);
            void removeEntity(Entity &entity);
            const std::map<uint32_t, std::vector<Entity *>> &getEntities() const;

            void activateCollisions();
            void deactivateCollisions();
            bool getCollisionStatus() const;

            void setVerticalScanline();
            void setHorizontalScanline();
            scanline_t getScanlineStatus() const;

        protected:
            bool horizontalSort(Entity *e1, Entity *e2);
            bool verticalSort(Entity *e1, Entity *e2);
            void sortEntities();
            void removeDeletedEntities();
            void scanline();
            float scanMin(Entity *e);
            float scanMax(Entity *e);

    };

}
