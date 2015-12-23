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

        for (std::list<GameWindow*>::iterator
             gameWindowIt=gameWindows.begin();
             gameWindowIt != gameWindows.end(); ++gameWindowIt) {
            
            GameWindow *gameWindow = *gameWindowIt;
            assert(gameWindow != NULL);
            gameWindow->render();
    
        }

//        GameLoop::inst().getRenderWindow().display();
    
    }
    
    void GameState::update(const sf::Time &tslu) {

        inputManager.processInput();
    
        for (std::list<GameWorld*>::iterator
             gameWorldIt=gameWorlds.begin();
             gameWorldIt != gameWorlds.end(); ++gameWorldIt) {
            
            GameWorld *gameWorld = *gameWorldIt;
            assert(gameWorld != NULL);
            gameWorld->update(tslu);
    
        }
    
    }
    
    std::list<GameWorld*> & GameState::accessGameWorlds() {
        return gameWorlds;
    }
    
    std::list<GameWindow*> & GameState::accessGameWindows() {
        return gameWindows;
    }
    
    InputManager & GameState::accessInputManager() {
        return inputManager;
    }

}
