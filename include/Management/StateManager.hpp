#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include <Shogun/Management/GameState.hpp>

namespace sg {

    class StateManager {

        public:
            static StateManager & inst();

            void pushState(GameState &state);
            GameState *popState();
            GameState *peekState() const;

            ~StateManager() {}

        private:
            std::stack<GameState *> states;
            bool paused = false;

            StateManager() {}
            StateManager(StateManager const&) = delete;
            void operator=(StateManager const&) = delete;

    };

}
