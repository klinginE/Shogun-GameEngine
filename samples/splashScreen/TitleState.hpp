#pragma once

//Shogun includes
#include <Shogun/Management/GameWindow.hpp>
#include <Shogun/Management/GameWorld.hpp>

//Sol Crusade includes
#include "MainGame.hpp"
#include "BaseState.hpp"

#define FADE_RATE 1
#define FADE_DELAY 30

class TitleState : public BaseState {

    private:
        sg::GameWindow tWindow;
        sg::GameWorld tWorld;
        sf::Font arial;
        sf::Text developed;
        sf::Text presents;
        sf::Text title;
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sg::Entity textEntity;
        uint32_t fadeTimer = 0;
        bool fadeIn = true;
        int fadeAlpha = 0;

    public:
        TitleState();
        void update(const sf::Time &tslu);

};
