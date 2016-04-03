#include <list>
#include <assert.h>

#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Management/GameWorld.hpp>
#include <Shogun/Management/GameWindow.hpp>
#include <Shogun/Management/InputManager.hpp>

#include <Shogun/Management/GameState.hpp>

namespace sg {
    
    GameState::GameState() {
        renderOrder = [=](const GameWindow &w1, const GameWindow &w2) -> bool {return false;};
    }
    
    void GameState::render() {

        GameLoop::inst().getRenderWindow().clear(sf::Color::Black);

        auto comp = [=](GameWindow *w1, GameWindow *w2)->bool{return renderOrder(*w1, *w2);};
        std::sort(gameWindows.begin(), gameWindows.end(), comp);

        for (auto gameWindowIt=gameWindows.begin();
             gameWindowIt != gameWindows.end(); ++gameWindowIt) {
           
            GameWindow *gameWindow = *gameWindowIt;
            assert(gameWindow != NULL);
            gameWindow->render();
    
        }

        GameLoop::inst().getRenderWindow().display();
    
    }
    
    void GameState::update(const sf::Time &tslu) {

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
    
    const GameWindow * GameState::getWindow(uint32_t windowIdx) const {
        if (windowIdx >= gameWindows.size())
            return NULL; // return NULl if not found
        return gameWindows[windowIdx];
    }

    const GameWorld * GameState::getWorld(uint32_t worldIdx) const {
        if (worldIdx >= gameWorlds.size())
            return NULL; // return NULl if not found
        return gameWorlds[worldIdx];
    }

    const GameWindow * GameState::removeWindow(uint32_t windowIdx) {
        if (windowIdx >= gameWindows.size())
            return NULL;
        GameWindow *gameWindow = gameWindows[windowIdx];
        gameWindows.erase(gameWindows.begin() + windowIdx);
        return gameWindow;
    }

    const GameWorld * GameState::removeWorld(uint32_t worldIdx) {
        if (worldIdx >= gameWorlds.size())
            return NULL;
        GameWorld *gameWorld = gameWorlds[worldIdx];
        gameWorlds.erase(gameWorlds.begin() + worldIdx);
        return gameWorld;
    }

    std::size_t GameState::getNumWindows() const {
        return gameWindows.size();
    }

    std::size_t GameState::getNumWorlds() const {
        return gameWorlds.size();
    }

    void GameState::setInputManager(const InputManager &newInputManager) {
        inputManager = &newInputManager;
    }

    const InputManager * GameState::removeInputManager() {
        const InputManager *oldInputManager = inputManager;
        inputManager = NULL;
        return oldInputManager;
    }

    const InputManager * GameState::getInputManager() const {
        return inputManager;
    }

}
