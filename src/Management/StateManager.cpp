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
    
        GameState *pausestate = peekState();
        states.push(&state);
        if (pausestate) pausestate->pause();
        state.enter();
    
    }
    
    GameState *StateManager::popState() {

        GameState *state = peekState();
        states.pop();
        state->leave();
        if (peekState()) peekState()->resume();
        return state;
    
    }
    
    GameState *StateManager::peekState() const {
    
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
