#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <list>

#include "GameWorld.hpp"
#include "GameWindow.hpp"
#include "InputManager.hpp"

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

#endif
