#include <limits>

#include <Shogun/Management/GameWorld.hpp>
#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/GameLoop.hpp>

#include <Shogun/Management/GameWorld.hpp>

namespace sg {

    // CONSTRUCTORS
    GameWorld::GameWorld() {

        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        this->worldBounds.left = std::numeric_limits<long>::min();
        this->worldBounds.top = std::numeric_limits<long>::min();
        this->worldBounds.width = std::numeric_limits<long>::max();
        this->worldBounds.height = std::numeric_limits<long>::max();

    }

    GameWorld::GameWorld(std::map<uint32_t, Layer *> ls) {

        this->layers = ls;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        this->worldBounds.left = std::numeric_limits<long>::min();
        this->worldBounds.top = std::numeric_limits<long>::min();
        this->worldBounds.width = std::numeric_limits<long>::max();
        this->worldBounds.height = std::numeric_limits<long>::max();
        for (auto it = layers.begin(); it != layers.end(); ++it)
            sortEntities(it->first);

    }

    void GameWorld::update(const sf::Time &tslu) {

        timespec ts0;
        timespec ts1;
        clock_gettime(CLOCK_REALTIME, &ts0);
        // delete entities that should be removed
        auto shouldBeRemoved = [](Entity *s) {
            return s->getDeletionStatus();
        };
        for (auto it = layers.begin(); it != layers.end(); ++it) {
            std::cout << " layer: " << it->first << " deletions status: " << it->second->deletionStatus << " ";
            if (it->second->deletionStatus) {

                auto el = it->second->getEntityList();
                el.erase(std::remove_if(el.begin(), el.end(), shouldBeRemoved), el.end());
                auto rl = it->second->getEntityList();
                rl.erase(std::remove_if(rl.begin(), rl.end(), shouldBeRemoved), rl.end());
                it->second->deletionStatus = false;

            }
        }
        std::cout << std::endl;
        clock_gettime(CLOCK_REALTIME, &ts1);
        std::cout << "WUD: " << (ts1.tv_nsec - ts0.tv_nsec) << std::endl;

        clock_gettime(CLOCK_REALTIME, &ts0);
        // update all entities
        for (auto it = layers.begin(); it != layers.end(); ++it)
            if (it->second->updateStatus)
                for (Entity *e : it->second->getEntityList())
                    e->update(tslu);
        clock_gettime(CLOCK_REALTIME, &ts1);
        std::cout << "WUU: " << (ts1.tv_nsec - ts0.tv_nsec) << std::endl;

        clock_gettime(CLOCK_REALTIME, &ts0);
        // Detect and resolve collisions between entities
        if (collisionActive)
            scanline();
        clock_gettime(CLOCK_REALTIME, &ts1);
        std::cout << "WUC: " << (ts1.tv_nsec - ts0.tv_nsec) << std::endl;

    }

    float GameWorld::scanMin(Entity *e) {

        if (scanlineType == scanline_t::HORIZONTAL)
            return e->getSurfaceBounds().left;

        return e->getSurfaceBounds().top;

    }

    float GameWorld::scanMax(Entity *e) {

        sf::FloatRect bounds = e->getSurfaceBounds();
        if (scanlineType == scanline_t::HORIZONTAL)
            return bounds.left + bounds.width;

        return bounds.top + bounds.height;

    }

    void GameWorld::scanline() {

        // scanline
        for (auto it = layers.begin(); it != layers.end(); ++it) {

            std::cout << " layer: " << it->first << " collision status: " << it->second->collisionStatus << " ";
            if (!it->second->collisionStatus)
                continue;

            // sort all entities before scanline
            sortEntities(it->first);
            //get entities
            auto entities = it->second->getEntityList();
            for (uint32_t i = 0; i < entities.size(); ++i) {

                if (!entities[i]->getIsCollidable())
                    continue;

                for (uint32_t j = i + 1; j < entities.size() && scanMin(entities[j]) <= scanMax(entities[i]); ++j) {

                    if (!entities[j]->getIsCollidable())
                        continue;

                    entities[i]->collides(*entities[j]);

                }

            }

       }
       std::cout << std::endl;

    }

    void GameWorld::addLayer(uint32_t level, Layer &l) {

        layers[level] = &l;

    }

    void GameWorld::removeLayer(uint32_t level) {

        layers.erase(level);

    }

    const Layer *GameWorld::getLayer(uint32_t level) const {

        return layers.at(level);

    }

    const std::map<uint32_t, Layer *> &GameWorld::getLayers() const {

        return layers;

    }

    void GameWorld::activateCollisions() {

        collisionActive = true;

    }

    void GameWorld::deactivateCollisions() {

        collisionActive = false;

    }

    bool GameWorld::getCollisionStatus() const {

        return collisionActive;

    }

    void GameWorld::setVerticalScanline() {

        scanlineType = scanline_t::VERTICAL;

    }

    void GameWorld::setHorizontalScanline() {

        scanlineType = scanline_t::HORIZONTAL;

    }

    scanline_t GameWorld::getScanlineStatus() const {

        return scanlineType;

    }

    bool verticalComparitor(const Entity *e1, const Entity *e2) {

        if (e1->getSurfaceBounds().top < e2->getSurfaceBounds().top)
            return true;

        return false;

    }

    bool horizontalComparitor(const Entity *e1, const Entity *e2) {

        if (e1->getSurfaceBounds().left < e2->getSurfaceBounds().left)
            return true;

        return false;

    }

    void GameWorld::sortEntities(uint32_t level) {

        //TODO:[RB]->Add deleted entities function to class
        //TODO:[EK]->Deleting here may be redudant. I would make sure you really want to do this before proceding.
        //removeDeletedEntities();

        std::cout << " layer: " << level << " sort status: " << layers[level]->sortStatus << std::endl;
        if (layers[level]->sortStatus) {

            if (scanlineType == scanline_t::VERTICAL)
                layers[level]->sortEntityList(verticalComparitor);
            else
                layers[level]->sortEntityList(horizontalComparitor);

        }

    }

}
