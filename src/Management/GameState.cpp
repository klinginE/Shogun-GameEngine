#include <list>
#include <assert.h>

#include <Shogun/Management/GameLoop.hpp>
#include <Shogun/Management/GameState.hpp>

namespace sg {

    GameState::GameState() {

        this->renderOrder = [=](const GameWindow &w1, const GameWindow &w2)->bool {return false;};

    }

    void GameState::render() {

        //sf::Clock cc;
        GameLoop::inst().getRenderWindow().clear(sf::Color::Transparent);
        //sf::Time ct = cc.restart();
        //std::cout << "Clear window time:      " << ct.asMicroseconds() << std::endl;

        //sf::Clock sc;
        auto comp = [=](GameWindow *w1, GameWindow *w2)->bool {return this->renderOrder(*w1, *w2);};
        std::sort(gameWindows.begin(), gameWindows.end(), comp);
        //sf::Time st = sc.restart();
        //std::cout << "sort windows time:      " << st.asMicroseconds() << std::endl;

        for (GameWindow *gameWindow : this->gameWindows)
            gameWindow->render();

        GameLoop::inst().getRenderWindow().display();

    }

    void GameState::update(const sf::Time &tslu) {

        for (GameWorld *gameWorld : gameWorlds)
            gameWorld->update(tslu);

    }

    void GameState::addWorld(GameWorld &newWorld) {

        gameWorlds.push_back(&newWorld);

    }

    void GameState::addWindow(GameWindow &newWindow) {

        gameWindows.push_back(&newWindow);

    }

    const GameWindow *GameState::getWindow(uint32_t windowIdx) const {

        if (windowIdx >= gameWindows.size())
            return NULL; // return NULl if not found

        return gameWindows[windowIdx];

    }

    const GameWorld * GameState::getWorld(uint32_t worldIdx) const {

        if (worldIdx >= gameWorlds.size())
            return NULL; // return NULl if not found

        return gameWorlds[worldIdx];

    }

    const GameWindow *GameState::removeWindow(uint32_t windowIdx) {

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

    std::vector<GameWindow *>::size_type GameState::getNumWindows() const {

        return gameWindows.size();

    }

    std::vector<GameWorld *>::size_type GameState::getNumWorlds() const {

        return gameWorlds.size();

    }

    void GameState::setInputManager(const InputManager &newInputManager) {

        inputManager = &newInputManager;

    }

    const InputManager *GameState::removeInputManager() {

        const InputManager *oldInputManager = inputManager;
        inputManager = NULL;

        return oldInputManager;

    }

    const InputManager *GameState::getInputManager() const {

        return inputManager;

    }

}
