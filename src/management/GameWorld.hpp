#pragma once

#include <vector>
#include <set>
#include <SFML/Graphics.hpp>

#include "../elements/Entity.hpp"
#include "InputManager.hpp"

namespace sg {

    enum scanline_t : bool {
        VERTICAL,
        HORIZONTAL
    };
    
    class GameWorld {
    
        //std::vector<sf::Sprite *> background; // TODO: implemenet fuctions for this, and with GameWindow
        std::set<Entity *> deleteSet;
        std::vector<Entity *> entities;
        InputManager *inputManager;

        bool inputActive;
        scanline_t scanlineType;
        bool collisionActive;
    
        public:
            GameWorld();
            GameWorld(InputManager *inputManager);
            GameWorld(std::vector<Entity *> entities);
            GameWorld(InputManager *inputManager,
                      std::vector<Entity *> entities);
            
            virtual void update(const sf::Time &);

            void addEntity(Entity *entity);
            void removeEntity(Entity *entity);
            std::vector<Entity *> getEntities();
            
            void activateCollisions();
            void deactivateCollisions();
            bool getCollisionStatus();

            void activateInput();
            void deactivateInput();
            bool getInputStatus();

            void setVerticalScanline();
            void setHorizontalScanline();
            scanline_t getScanlineStatus();

            void setInputManager(InputManager *);

        private:
            bool horizontalSort(Entity *e1, Entity *e2);
            bool verticalSort(Entity *e1, Entity *e2);
            void sortEntities();
            void removeDeletedEntities();
            void scanline();
            float scanMin(Entity *e);
            float scanMax(Entity *e);

    };

}
