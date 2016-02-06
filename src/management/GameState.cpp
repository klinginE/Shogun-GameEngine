#include <list>
#include <assert.h>

#include "GameLoop.hpp"
#include "GameWorld.hpp"
#include "GameWindow.hpp"
#include "InputManager.hpp"

#include "GameState.hpp"

namespace sg {
    
    GameState::GameState() {
        // Nothing is in the constructor
    }
    
    void GameState::render() {

//        GameLoop::inst().getRenderWindow().clear(sf::Color::Black);

        for (auto gameWindowIt=gameWindows.begin();
             gameWindowIt != gameWindows.end(); ++gameWindowIt) {
           
            GameWindow *gameWindow = *gameWindowIt;
            assert(gameWindow != NULL);
            gameWindow->render();
    
        }

//        GameLoop::inst().getRenderWindow().display();
    
    }
    
    void GameState::update(const sf::Time &tslu) {

        if (inputManager)
            inputManager->processInput(tslu);
    
        for (auto gameWorldIt=gameWorlds.begin();
             gameWorldIt != gameWorlds.end(); ++gameWorldIt) {
            
            GameWorld *gameWorld = *gameWorldIt;
            assert(gameWorld != NULL);
            gameWorld->update(tslu);
    
        }
    
    }
    
    void GameState::addWorld(GameWorld &newWorld) {
        gameWorlds.push_back(&newWorld);
    }

    void GameState::addWindow(GameWindow &newWindow) {
        gameWindows.push_back(&newWindow);
    }
    
    const GameWindow * GameState::getWindow(uint32_t windowIdx) {
        if (windowIdx >= gameWindows.size())
            return NULL; // return NULl if not found
        return gameWindows[windowIdx];
    }

    const GameWorld * GameState::getWorld(uint32_t worldIdx) {
        if (worldIdx >= gameWorlds.size())
            return NULL; // return NULl if not found
        return gameWorlds[worldIdx];
    }

    std::size_t GameState::getNumWindows() {
        return gameWindows.size();
    }

    std::size_t GameState::getNumWorlds() {
        return gameWorlds.size();
    }

    InputManager * GameState::getInputManager() {
        return inputManager;
    }

    void GameState::setInputManager(InputManager &newInputManager) {
        inputManager = &newInputManager;
    }

}
