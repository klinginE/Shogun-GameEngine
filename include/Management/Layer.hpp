#pragma once

#include <functional>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include <Shogun/Management/Quadtree.hpp>
#include <Shogun/Management/Quadtree.t.hpp>
#include <Shogun/Elements/Entity.hpp>

namespace sg {

    enum scanline_t : bool {
        VERTICAL,
        HORIZONTAL
    };

    class Layer {

        private:
            sf::Rect<long> globalArea;
            Quadtree<Entity *> dynamicEntities;
            Quadtree<Entity *> staticEntities;
            std::function<bool(const Entity *, const Entity *)> renderOrder;
            scanline_t scanlineDir;

            sf::Rect<long> convertBounds(const sf::FloatRect &) const;
            float scanMin(const Entity *e) const;
            float scanMax(const Entity *e) const;
            void scanline(std::vector<Entity *> &) const;

        protected:
            virtual void processCollisions(std::map<std::pair<Entity *, Entity *>, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f>> &) const;

        public:
            bool updateStatus;
            bool collisionStatus;
            bool renderStatus;
            bool renderSortStatus;
            sf::Rect<long> updateArea;
            sf::Rect<long> renderArea;

            Layer();
            virtual ~Layer() {}
            const Quadtree<Entity *> &getDynamicEntities() const;
            const Quadtree<Entity *> &getStaticEntities() const;
            const std::function<bool(const Entity *, const Entity *)> getRenderOrder() const;
            void addDynamicEntity(Entity &);
            void addStaticEntity(Entity &);
            bool removeEntity(Entity &);
            bool removeDynamicEntity(Entity &);
            bool removeStaticEntity(Entity &);
            void setRenderOrder(std::function<bool(const Entity *, const Entity *)>);
            virtual void update(const sf::Time &);
            virtual void render();
            void setVerticalScanline();
            void setHorizontalScanline();
            scanline_t getScanlineStatus() const;

    };

}
