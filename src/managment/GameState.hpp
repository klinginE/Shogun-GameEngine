#pragma once

#include <list>

#include "GameWorld.hpp"
#include "GameWindow.hpp"
#include "InputManager.hpp"

namespace sg {

    class GameState {
    
        std::list<GameWorld*> gameWorlds;
        std::list<GameWindow*> gameWindows;
        InputManager inputManager;
    
        public:
            GameState();
    
            void render();
            void update(const sf::Time &tslu);
    
            std::list<GameWorld*>  & accessGameWorlds();
            std::list<GameWindow*> & accessGameWindows();
            InputManager           & accessInputManager();
    };
    
}
