#include <limits>
#include <queue>

#include <Shogun/Management/Layer.hpp>

namespace sg
{
    Layer::Layer()
    {
        double longOriginAsDouble = static_cast<double>(std::numeric_limits<long>::min()) / 2.0;
        if (longOriginAsDouble < 0.0)
        {
            longOriginAsDouble = std::floor(longOriginAsDouble);
        }
        else
        {
            longOriginAsDouble = std::ceil(longOriginAsDouble);
        }
        long longOrigin = static_cast<long>(longOriginAsDouble);
        long longMax = std::numeric_limits<long>::max();
        this->globalArea = sf::Rect<long>(longOrigin,
                                          longOrigin,
                                          longMax,
                                          longMax);

        this->updateArea.left = this->globalArea.left;
        this->updateArea.top = this->globalArea.top;
        this->updateArea.width = this->globalArea.width;
        this->updateArea.height = this->globalArea.height;

        this->renderArea.left = this->globalArea.left;
        this->renderArea.top = this->globalArea.top;
        this->renderArea.width = this->globalArea.width;
        this->renderArea.height = this->globalArea.height;

        this->dynamicEntities.init(1, std::numeric_limits<uint64_t>::max(), 0, this->globalArea);
        this->staticEntities.init(1, std::numeric_limits<uint64_t>::max(), 0, this->globalArea);

        this->renderOrder = [=](const Entity *e0, const Entity *e1)->bool {return false;};

        this->scanlineDir = scanline_t::HORIZONTAL;

        this->updateStatus = true;
        this->collisionStatus = true;
        this->renderStatus = true;
        this->renderSortStatus = true;
    }

    const Quadtree<Entity *> &Layer::getDynamicEntities() const
    {
        return this->dynamicEntities;
    }

    const Quadtree<Entity *> &Layer::getStaticEntities() const
    {
        return this->staticEntities;
    }

    const std::function<bool(const Entity *, const Entity *)> Layer::getRenderOrder() const
    {
        return this->renderOrder;
    }

    void Layer::addDynamicEntity(Entity &newE)
    {
        this->dynamicEntities.insert(this->convertBounds(newE.getTotalBounds(true)), &newE);
    }

    void Layer::addStaticEntity(Entity &newE)
    {
        this->staticEntities.insert(this->convertBounds(newE.getTotalBounds(true)), &newE);
    }

    bool Layer::removeEntity(Entity &re)
    {
        if (!this->removeDynamicEntity(re))
        {
            return this->removeStaticEntity(re);
        }

        return true;
    }

    bool Layer::removeDynamicEntity(Entity &re)
    {
        return this->dynamicEntities.remove(this->convertBounds(re.getTotalBounds(true)), &re);
    }

    bool Layer::removeStaticEntity(Entity &re)
    {
        return this->staticEntities.remove(this->convertBounds(re.getTotalBounds(true)), &re);
    }

    sf::Rect<long> Layer::convertBounds(const sf::FloatRect &fb) const
    {
        sf::Rect<long> lb;

        double roundedLeft = 0.0;
        if (fb.left < 0.0)
        {
            roundedLeft = std::floor(fb.left);
        }
        else
        {
            roundedLeft = std::ceil(fb.left);
        }
        lb.left = static_cast<long>(roundedLeft);

        double roundedTop = 0.0;
        if (fb.top < 0.0)
        {
            roundedTop = std::floor(fb.top);
        }
        else
        {
            roundedTop = std::ceil(fb.top);
        }
        lb.top = static_cast<long>(roundedTop);

        double roundedWidth = 0.0;
        if (fb.width < 0.0)
        {
            roundedWidth = std::floor(fb.width);
        }
        else
        {
            roundedWidth = std::ceil(fb.width);
        }
        lb.width = static_cast<long>(roundedWidth);

        double roundedHeight = 0.0;
        if (fb.height < 0.0)
        {
            roundedHeight = std::floor(fb.height);
        }
        else
        {
            roundedHeight = std::ceil(fb.height);
        }
        lb.height = static_cast<long>(roundedHeight);

        return lb;
    }

    void Layer::setRenderOrder(std::function<bool(const Entity *, const Entity *)> newRO)
    {
        this->renderOrder = newRO;
    }

    void Layer::update(const sf::Time &tslu)
    {
        //sf::Clock gc_preColl;
        if (!this->updateStatus)
        {
            return;
        }

        std::vector<Entity *> entities;

        //update dynamic
        std::vector<Entity *> d_entities;
        this->dynamicEntities.retrieve(d_entities, this->globalArea);
        this->dynamicEntities.clear();
        for (Entity *e : d_entities)
        {
            if (!e->getDeletionStatus())
            {
                if (this->dynamicEntities.boundsOverlap(this->convertBounds(e->getTotalBounds(true)),
                                                        this->updateArea))
                {
                    e->update(tslu);
                }
                entities.push_back(e);
                this->addDynamicEntity(*e);
            }
        }

        //update static
        std::vector<Entity *> s_entities;
        this->staticEntities.retrieve(s_entities, this->updateArea);
        for (Entity *e : s_entities)
        {
            if (!e->getDeletionStatus())
            {
                e->update(tslu);
                entities.push_back(e);
            }
            else
            {
                this->staticEntities.remove(this->convertBounds(e->getTotalBounds(true)), e);
            }
        }
        //sf::Time timePreColl = gc_preColl.restart();
        //std::cout << "Pre collides time:  " << timePreColl.asMicroseconds() << std::endl;

        //sf::Clock gc_coll;
        if (this->collisionStatus)
        {
            this->scanline(entities);
        }
        //sf::Time timePosColl = gc_coll.restart();
        //std::cout << "Post collides time: " << timePosColl.asMicroseconds() << std::endl;
    }

    void Layer::render()
    {
        if (!this->renderStatus)
        {
            return;
        }

        //sf::Clock gc;
        //gather entities
        std::vector<Entity *> entities;
        this->dynamicEntities.retrieve(entities, this->renderArea);
        this->staticEntities.retrieve(entities, this->renderArea);
        //sf::Time gt = gc.restart();

        //sf::Clock dc;
        //sort based on render order and draw
        if (this->renderSortStatus)
        {
            std::sort(entities.begin(), entities.end(), this->renderOrder);
        }
        for (Entity *e : entities)
        {
            e->draw();
        }
        //sf::Time dt = dc.restart();
    }

    void Layer::setVerticalScanline()
    {
        this->scanlineDir = scanline_t::VERTICAL;
    }

    void Layer::setHorizontalScanline()
    {
        this->scanlineDir = scanline_t::HORIZONTAL;
    }

    scanline_t Layer::getScanlineStatus() const
    {
        return this->scanlineDir;
    }

    bool verticalComparitor(const Entity *e1, const Entity *e2)
    {
        if (e1->getSurfaceBounds(true).top < e2->getSurfaceBounds(true).top)
        {
            return true;
        }

        return false;
    }

    bool horizontalComparitor(const Entity *e1, const Entity *e2)
    {
        if (e1->getSurfaceBounds(true).left < e2->getSurfaceBounds(true).left)
        {
            return true;
        }

        return false;
    }

    float Layer::scanMin(const Entity *e) const
    {
        if (this->scanlineDir == scanline_t::HORIZONTAL)
        {
            return e->getSurfaceBounds(true).left;
        }

        return e->getSurfaceBounds(true).top;
    }

    float Layer::scanMax(const Entity *e) const
    {
        sf::FloatRect bounds = e->getSurfaceBounds(true);
        if (scanlineDir == scanline_t::HORIZONTAL)
        {
            return bounds.left + bounds.width;
        }

        return bounds.top + bounds.height;
    }

    void Layer::processCollisions(std::map<std::pair<Entity *, Entity *>, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f>> &collisionPairs) const
    {
        for (std::pair<std::pair<Entity *, Entity *>, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f>> p : collisionPairs)
        {
            Entity *e0 = p.first.first;
            Entity *e1 = p.first.second;
            std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f> collisionMap0 = p.second;

            std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f> collisionMap1;
            for (std::pair<std::pair<uint64_t, uint64_t>, sf::Vector2f> obj0 : collisionMap0)
            {
                std::pair<uint64_t, uint64_t> mp = obj0.first;
                sf::Vector2f vector = obj0.second;
                collisionMap1[std::make_pair(mp.second, mp.first)] = -vector;
            }

            e0->handleCollision(*e1, collisionMap0);
            e1->handleCollision(*e0, collisionMap1);
        }
    }

    void Layer::scanline(std::vector<Entity *> &entities) const
    {
        std::map<std::pair<Entity *, Entity *>, std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f>> collisionPairs;

        for (Entity *e0 : entities)
        {
            if (e0->getIsCollidable())
            {
                std::vector<Entity *> possible;
                sf::Rect<long> e0Bounds = this->convertBounds(e0->getTotalBounds(true));
                this->dynamicEntities.retrieve(possible, e0Bounds);
                this->staticEntities.retrieve(possible, e0Bounds);

                //sort
                if (this->scanlineDir == scanline_t::HORIZONTAL)
                {
                    std::sort(possible.begin(), possible.end(), horizontalComparitor);
                }
                else
                {
                    std::sort(possible.begin(), possible.end(), verticalComparitor);
                }

                float scanMax = this->scanMax(e0);
                for (uint32_t i = 0; i < possible.size() && scanMin(possible[i]) <= scanMax; ++i)
                {
                    Entity *e1 = possible[i];
                    if (e1->getIsCollidable() && e0 != e1)
                    {
                        std::map<std::pair<uint64_t, uint64_t>, sf::Vector2f> collisionMap;
                        bool collides = e0->collides(*e1, collisionMap);
                        if (collides)
                        {
                            collisionPairs[std::make_pair(e0, e1)] = collisionMap;
                        }
                    }
                }
            }
        }

        this->processCollisions(collisionPairs);

    }
}
