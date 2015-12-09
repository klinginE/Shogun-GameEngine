#include <SFML/Vector2.hpp>

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "GameLoop.hpp"

#include "GameWorld.hpp"

namespace sg {
    
    // CONSTRUCTORS

    GameWorld::GameWorld() {
        inputManager = NULL;
        inputActive = false;
        scanlineType = scanline_t::HORIZONTAL;
        collisionActive = true;
    }
    GameWorld::GameWorld(InputManager *inputManager) {
        this->inputManager = inputManager;
        this->inputActive = true;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
    }
    GameWorld::GameWorld(std::vector<Entity *> entities) {
        this->entities = entities;
        this->inputManager = NULL;
        this->inputActive = false;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        sortEntities();
    }
    GameWorld::GameWorld(InputManager *inputManager,
                         std::vector<Entity *> entities) {
        this->entities = entities;
        this->inputManager = inputManager;
        this->inputActive = true;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        // TODO: sort entities here
        sortEntities();
    }

    void GameWorld::update() {
        // process input
        if (inputActive && inputManager)
            inputManager->processInput();
        // update all entities
        for (auto entityIter = entities.begin();
             entityIter != entities.end(); ++entitiyIter) {
            Entity *e = *entityIter;
            e->update();
        }
        // Detect and resolve collisions between entities
        if (collisionActive)
            scanline();
    }

    float GameWorld::getMinX(Entity *e) {
        return e->getPos().x + e->getSprite()->getGlobalBounds().left;
    }
    float GameWorld::getMaxX(Entity *e) {
        return e->getPos().x
             + e->getSprite()->getGlobalBounds().left
             + e->getSprite()->getGlobalBounds().width;
    }
    float GameWorld::getMinY(Entity *e) {
        return e->getPos().y
             + e->getSprite()->getGlobalBounds().top
             + e->getSprite()->getGlobalBounds().height;
    }
    float GameWorld::getMaxY(Entity *e) {
        return e->getPos().y
             + e->getSprite()->getGlobalBounds().top
             + e->getSprite()->getGlobalBounds().height;
    }

    void GameWorld::scanline() {
        // sort all entities before scanline 
        sortEntities();
        
        // TODO: scanline
        for (auto i1 = entities.begin();
             i1 != entities.end(); ++i1) {
            Entity *e1 = *i1;

            if (!getIsCollidable(e1))
                continue;

            for (auto i2 = i1;
                 i2 != entities.end && getMinX(*i2) <= getMaxX(e1);
                 ++i2) {
                
                Entity *e2 = *i2;

                if (!getIsCollidable(e2))
                    continue;

                e1->collides(*e2);

            }
        }
    }

    void GameWorld::addEntity(Entity *entity) {
        entities.push_back(entity);
    }
    bool GameWorld::removeEntity(Entity *entity) {
        deleteSet.insert(entity);
    }
    std::vector<Entity *> GameWorld::getEntities() {
        return entities;
    }

    void GameWorld::activateCollisions() {
        collisionActive = true;
    }
    void GameWorld::deactivateCollisions() {
        collisionActive = false;
    }
    bool GameWorld::getCollisionStatus() {
        return collisionAcive;
    }

    void GameWorld::activateInput() {
        inputActive = true;
    }
    void GameWorld::deactivateInput() {
        inputActive = false;
    }
    bool GameWorld::getInputStatus() {
        return inputActive;
    }

    void GameWorld::setVerticalScanline() {
        scanlineType = scanline_t::VERTICAL;
    }
    void GameWorld::setHorizontalScanline() {
        scanlineType = scanline_t::HORIZONTAL;
    }
    scanline_t GameWorld::getScanlineStatus() {
        return scanlineType;
    }

    void GameWorld::setInputManager(InputManager * inputManager) {
        this->inputManager = inputManager;
    }

    bool GameWorld::horizontalSort(Entity *e1, Entity *e2) {
        if (e1->getPos().x + e1->getSprite()->getGlobalBounds().left
          < e2->getPos().x + e2->getSprite()->getGlobalBounds().left)
            return true;
        else
            return false;
    }
    bool GameWorld::verticalSort(Entity *e1, Entity *e2) {
        if (e1->getPos().y + e1->getSprite()->getGlobalBounds().top
          < e2->getPos().y + e2->getSprite()->getGlobalBounds().top)
            return true;
        else
            return false;
    }

    void GameWorld::sortEntities() {
        removeDeletedEntiteis();
        if (scanlineType == scanline_t::VERTICAL) {
            std::sort(entities.begin(), entities.end(),
                      verticalSort);
        }
        else {
            std::sort(entities.begin(), entities.end(),
                      horizontalSort);
        }
    }

}
