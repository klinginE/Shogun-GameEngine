#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "StateManager.hpp"
#include "GameState.hpp"

StateManager & StateManager::inst() {

    static StateManager instance;
    
    return instance;

}

void StateManager::pushState(GameState *state) {

    states.push(state);

}

GameState *StateManager::popState() {

    GameState *state = states.top();
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


