#pragma once

#include <vector>

#include "GameWorld.hpp"
#include "GameWindow.hpp"
#include "InputManager.hpp"

namespace sg {

    class GameState {

        private: 
            std::vector<GameWorld*> gameWorlds;
            std::vector<GameWindow*> gameWindows;
            InputManager *inputManager = NULL;

        public:
            GameState();
 
            virtual void render();
            virtual void update(const sf::Time &tslu);

            void addWindow(GameWindow &);
            void addWorld(GameWorld &);

            const GameWindow *getWindow(uint32_t);
            const GameWorld *getWorld(uint32_t);

            std::size_t getNumWindows();
            std::size_t getNumWorlds();

            void setInputManager(InputManager &);
            InputManager *getInputManager();

    };
    
}
