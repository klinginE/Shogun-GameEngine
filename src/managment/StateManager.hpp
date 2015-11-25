#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "GameState.hpp"

namespace sg {
    
    class StateManager {
    
        public:
            static StateManager & getInst();
            
            void pushState(GameState *state);
            void popState();
            GameState *peekState();
    
            ~StateManager();
    
        private:
            
            std::stack<GameState *> states;
    
            StateManager() {};
            StateManager(StateManager const&) = delete;
            void operator=(StateManager const&) = delete;
            bool paused = false;
    };

}
