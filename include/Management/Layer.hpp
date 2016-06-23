#pragma once

#include <functional>
#include <vector>

#include <Shogun/Management/Quadtree.hpp>

namespace sg {

    class Entity;

    class Layer {

        private:
            std::vector<Entity *> entityList;
            //Quadtree<Entity *> renderList;
            std::vector<Entity *> renderList;
            std::function<bool(const Entity *, const Entity *)> renderOrder = [=](const Entity *e0, const Entity *e1)->bool {return false;};

        public:
            const std::vector<Entity *> &getEntityList() const;
            //const Quadtree<Entity *> &getRenderList() const;
            const std::vector<Entity *> &getRenderList() const;
            const std::function<bool(const Entity *, const Entity *)> getRenderOrder() const;
            void addEntity(Entity &);
            void removeEntity(Entity &);
            void setRenderOrder(std::function<bool(const Entity *, const Entity *)>);
            void sortEntityList(std::function<bool(const Entity *, const Entity *)>);
            void sortRenderList(std::function<bool(const Entity *, const Entity *)>);

            bool collisionStatus = true;
            bool deletionStatus = false;
            bool sortStatus = false;
            bool updateStatus = true;
            bool renderStatus = true;

    };

}
