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
            const InputManager *inputManager = NULL;

        public:
            GameState();
 
            virtual void render();
            virtual void update(const sf::Time &tslu);

            void addWindow(GameWindow &);
            void addWorld(GameWorld &);

            const GameWindow * getWindow(uint32_t);
            const GameWorld * getWorld(uint32_t);

            const GameWindow * removeWindow(uint32_t);
            const GameWorld * removeWorld(uint32_t);

            std::size_t getNumWindows();
            std::size_t getNumWorlds();

            void setInputManager(const InputManager &);
            const InputManager * removeInputManager();
            const InputManager * getInputManager();

    };
    
}
