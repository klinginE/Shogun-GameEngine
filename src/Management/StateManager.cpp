#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Shogun/Management/StateManager.hpp>
#include <Shogun/Management/GameState.hpp>

namespace sg {
    
    StateManager & StateManager::inst() {
    
        static StateManager instance;
        
        return instance;
    
    }
    
    void StateManager::pushState(GameState &state) {
    
        states.push(&state);
    
    }
    
    GameState *StateManager::popState() {

        GameState *state = peekState();
        states.pop();
        return state;
    
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
