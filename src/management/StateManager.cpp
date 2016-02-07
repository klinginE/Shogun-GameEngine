#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "StateManager.hpp"
#include "GameState.hpp"

namespace sg {
    
    StateManager & StateManager::inst() {
    
        static StateManager instance;
        
        return instance;
    
    }
    
    void StateManager::pushState(GameState &state) {
    
        states.push(&state);
    
    }
    
    void StateManager::popState() {
    
        states.pop();
    
    }
    
    GameState *StateManager::peekState() {
    
        if (this->states.empty()) {
    
            return NULL;
    
        }
    
        return states.top();
    
    }
    
    StateManager::~StateManager() {
    
        while (!states.empty()) {
    
            popState();
    
        }
    
    }
    
}
