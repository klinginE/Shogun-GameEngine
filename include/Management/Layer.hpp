#pragma once

#include <functional>
#include <vector>

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

            sf::Rect<long> convertBounds(const sf::FloatRect &);
            //bool verticalComparitor(const Entity *e1, const Entity *e2);
            //bool horizontalComparitor(const Entity *e1, const Entity *e2);
            float scanMin(const Entity *e) const;
            float scanMax(const Entity *e) const;
            void scanline(std::vector<Entity *> &) const;

        public:
            sf::Rect<long> updateArea;
            sf::Rect<long> renderArea;
            bool updateStatus;
            bool collisionStatus;
            bool renderStatus;
            bool renderSortStatus;

            Layer();
            virtual ~Layer() {}
            const Quadtree<Entity *> &getDynamicEntities() const;
            const Quadtree<Entity *> &getStaticEntities() const;
            const std::function<bool(const Entity *, const Entity *)> getRenderOrder() const;
            void addDynamicEntity(Entity &);
            void addStaticEntity(Entity &);
            void removeEntity(Entity &);
            void removeDynamicEntity(Entity &);
            void removeStaticEntity(Entity &);
            void setRenderOrder(std::function<bool(const Entity *, const Entity *)>);
            virtual void update(const sf::Time &);
            virtual void render();
            void setVerticalScanline();
            void setHorizontalScanline();
            scanline_t getScanlineStatus() const;

    };

}
