#pragma once

#include <list>

#include "GameWorld.hpp"
#include "GameWindow.hpp"
#include "InputManager.hpp"

namespace sg {

    class GameState {
    
        list<GameWorld*> gameWorlds;
        list<GameWindow*> gameWindows;
        InputManager inputManager;
    
        public:
            GameState();
    
            void render();
            void update(const sf::Time &tslu);
    
            list<GameWorld*>  & accessGameWorlds();
            list<GameWindow*> & accessGameWindows();
            InputManager      & accessInputManager();
    };
    
}
