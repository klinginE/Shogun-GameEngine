#include "GameWorld.hpp"
#include "../elements/Entity.hpp"
#include "GameLoop.hpp"

#include "GameWorld.hpp"

namespace sg {
    
    // CONSTRUCTORS

    GameWorld::GameWorld() {
        scanlineType = scanline_t::HORIZONTAL;
        collisionActive = true;
    }
    GameWorld::GameWorld(std::vector<Entity *> entities) {
        this->entities = entities;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        sortEntities();
    }

    void GameWorld::update(const sf::Time &tslu) {

        // delete entities that should be removed
        auto shouldBeRemoved = [](Entity * s) {
            if (s->getDeletionStatus())
                return true;
            else
                return false;
        };
        entities.erase(std::remove_if(entities.begin(), entities.end(), shouldBeRemoved), entities.end());
        // update all entities
        for (auto entityIter = entities.begin();
             entityIter != entities.end(); ++entityIter) {
            Entity *e = *entityIter;
            e->update(tslu);
        }
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
        if (scanlineType == scanline_t::HORIZONTAL)
            return e->getSurfaceBounds().left
                 + e->getSurfaceBounds().width;

        return e->getSurfaceBounds().top
             + e->getSurfaceBounds().height;
    }

    void GameWorld::scanline() {
        // sort all entities before scanline 
        sortEntities();
        
        // scanline
        for (auto i1 = entities.begin();
             i1 != entities.end(); ++i1) {
            Entity *e1 = *i1;

            if (!e1->getIsCollidable())
                continue;

            for (auto i2 = i1 + 1;
                 i2 != entities.end() && scanMin(*i2) <= scanMax(e1);
                 ++i2) {
                
                Entity *e2 = *i2;

                if (!e2->getIsCollidable())
                    continue;

                e1->collides(*e2);

            }
        }
    }

    void GameWorld::addEntity(Entity &entity) {
        entities.push_back(&entity);
    }
    const std::vector<Entity *> & GameWorld::getEntities() const {
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
        //TODO:Add deleted entities function to class
        //removeDeletedEntities();
        if (scanlineType == scanline_t::VERTICAL) {
            std::sort(entities.begin(), entities.end(),
                      verticalComparitor);
        }
        else {
            std::sort(entities.begin(), entities.end(),
                      horizontalComparitor);
        }
    }

}
