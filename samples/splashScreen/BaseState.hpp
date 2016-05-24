#pragma once

#include <Shogun/Management/GameState.hpp>

#include "MainGame.hpp"

class BaseState : public sg::GameState {

    protected:
        sg::InputManager im;

    public:
        BaseState();

};
