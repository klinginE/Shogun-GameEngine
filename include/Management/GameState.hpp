#pragma once

#include <vector>
#include <iostream>

#include <Shogun/Management/GameWorld.hpp>
#include <Shogun/Management/GameWindow.hpp>
#include <Shogun/Management/InputManager.hpp>

namespace sg {

    class GameState {

        private: 
            std::vector<GameWorld *> gameWorlds;
            std::vector<GameWindow *> gameWindows;
            const InputManager *inputManager = NULL;
            std::function<bool(const GameWindow &, const GameWindow &)>
                    renderOrder;

        public:
            GameState();
            virtual ~GameState() {}
 
            virtual void render();
            virtual void update(const sf::Time &tslu);
            virtual void enter() {}
            virtual void leave() {}
            virtual void pause() {}
            virtual void resume() {}

            void addWindow(GameWindow &);
            void addWorld(GameWorld &);

            const GameWindow *getWindow(uint32_t) const;
            const GameWorld *getWorld(uint32_t) const;

            const GameWindow *removeWindow(uint32_t);
            const GameWorld *removeWorld(uint32_t);

            std::vector<GameWindow *>::size_type getNumWindows() const;
            std::vector<GameWorld *>::size_type getNumWorlds() const;

            void setInputManager(const InputManager &);
            const InputManager *removeInputManager();
            const InputManager *getInputManager() const;

    };

}
