#include <Shogun/Management/GameWorld.hpp>
#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/GameLoop.hpp>

#include <Shogun/Management/GameWorld.hpp>

namespace sg {

    // CONSTRUCTORS
    GameWorld::GameWorld() {

        scanlineType = scanline_t::HORIZONTAL;
        collisionActive = true;

    }

    GameWorld::GameWorld(std::map<uint32_t, std::vector<Entity *>> entities) {

        this->entities = entities;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        sortEntities();

    }

    void GameWorld::update(const sf::Time &tslu) {

        // delete entities that should be removed
        auto shouldBeRemoved = [](Entity *s) {

            if (s->getDeletionStatus())
                return true;
            else
                return false;

        };
        for (auto it = entities.begin(); it != entities.end(); ++it)
            it->second.erase(std::remove_if(it->second.begin(), it->second.end(), shouldBeRemoved), it->second.end());

        // update all entities
        for (auto it = entities.begin(); it != entities.end(); ++it)
            for (Entity *e : it->second)
                e->update(tslu);
        // Detect and resolve collisions between entities
        if (collisionActive)
            scanline();

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

        // sort all entities before scanline
        sortEntities();

        // scanline
        for (auto it = entities.begin(); it != entities.end(); ++it) {

            for (uint32_t i = 0; i < it->second.size(); ++i) {

                if (!it->second[i]->getIsCollidable())
                    continue;

                for (uint32_t j = i + 1; j < it->second.size() && scanMin(it->second[j]) <= scanMax(it->second[i]); ++j) {

                    if (!it->second[j]->getIsCollidable())
                        continue;

                    it->second[i]->collides(*it->second[j]);

                }

            }

       }

    }

    void GameWorld::addEntity(uint32_t level, Entity &entity) {

        entities[level].push_back(&entity);

    }

    const std::map<uint32_t, std::vector<Entity *>> &GameWorld::getEntities() const {

        return entities;

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

    bool verticalComparitor(Entity *e1, Entity *e2) {

        if (e1->getSurfaceBounds().top < e2->getSurfaceBounds().top)
            return true;

        return false;

    }

    bool horizontalComparitor(Entity *e1, Entity *e2) {

        if (e1->getSurfaceBounds().left < e2->getSurfaceBounds().left)
            return true;

        return false;

    }

    void GameWorld::sortEntities() {

        //TODO:[RB]->Add deleted entities function to class
        //TODO:[EK]->Deleting here may be redudant. I would make sure you really want to do this before proceding.
        //removeDeletedEntities();

        for (auto it = entities.begin(); it != entities.end(); ++it)
            if (scanlineType == scanline_t::VERTICAL)
                std::sort(it->second.begin(), it->second.end(), verticalComparitor);
            else
                std::sort(it->second.begin(), it->second.end(), horizontalComparitor);

    }

}
