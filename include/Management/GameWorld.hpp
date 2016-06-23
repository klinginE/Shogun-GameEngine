#pragma once

//C++ Includes
#include <map>

//SFML Includes
#include <SFML/Graphics.hpp>

//Shogun Includes
#include <Shogun/Management/Layer.hpp>
#include <Shogun/Elements/Entity.hpp>

namespace sg {

    enum scanline_t : bool {
        VERTICAL,
        HORIZONTAL
    };

    class GameWorld {

        protected:
            std::map<uint32_t, Layer *> layers;
            scanline_t scanlineType;
            bool collisionActive;
            sf::Rect<long> worldBounds;

        public:
            GameWorld();
            GameWorld(std::map<uint32_t, Layer *>);
            virtual ~GameWorld() {}

            virtual void update(const sf::Time &);

            void addLayer(uint32_t, Layer &);
            void removeLayer(uint32_t);
            const Layer *getLayer(uint32_t) const;
            const std::map<uint32_t, Layer *> &getLayers() const;

            void activateCollisions();
            void deactivateCollisions();
            bool getCollisionStatus() const;

            void setVerticalScanline();
            void setHorizontalScanline();
            scanline_t getScanlineStatus() const;

        protected:
            bool horizontalSort(const Entity *e1, const Entity *e2);
            bool verticalSort(const Entity *e1, const Entity *e2);
            void sortEntities(uint32_t);
            void removeDeletedEntities();
            void scanline();
            float scanMin(Entity *e);
            float scanMax(Entity *e);

    };

}
