#include "TitleState.hpp"

#include <iostream>

TitleState::TitleState() :
BaseState()
{

    this->tWindow.setWorld(this->tWorld);
    this->tWindow.setPosInScreen(sf::Vector2f(0.0f, 0.0f));
    this->tWindow.setSizeInScreen(sf::Vector2f(1.0f, 1.0f));
    this->tWindow.setSizeInWorld(sf::Vector2f(MainGame::GAME_SIZE_FULL.x, MainGame::GAME_SIZE_FULL.y));
    this->tWindow.setPosInWorld(this->tWindow.getSizeInWorld()/2.0f);
    this->addWindow(tWindow);
    this->addWorld(tWorld);

    std::string fontPath(MainGame::RESOURCE_PATH + MainGame::PATH_DELIM + MainGame::FONTS_DIR + MainGame::PATH_DELIM + "arial.ttf");
    if (!arial.loadFromFile(fontPath))
        std::cerr << "Error, could not load font from file at: " << fontPath << std::endl;

    this->developed.setCharacterSize(30);
    this->developed.setStyle(sf::Text::Regular);
    this->developed.setFillColor(sf::Color(255, 255, 255, this->fadeAlpha));
    this->developed.setFont(arial);
    this->developed.setString("Developed Using Shogun Game Engine");
    this->developed.setOrigin(this->developed.getLocalBounds().width /2.0f, this->developed.getLocalBounds().height / 2.0f);
    this->developed.move(0.0f, 60.0f);

    this->textEntity.addDrawable(this->developed, false);

    this->logoTexture.loadFromFile(MainGame::RESOURCE_PATH + MainGame::PATH_DELIM + MainGame::IMAGES_DIR + MainGame::PATH_DELIM + "shogunLogo_white.png");
    this->logoSprite.setTexture(this->logoTexture);
    const sf::Color lcolor = this->logoSprite.getColor();
    this->logoSprite.setColor(sf::Color(lcolor.r, lcolor.g, lcolor.b, this->fadeAlpha));
    this->logoSprite.setOrigin(this->logoSprite.getLocalBounds().width / 2.0f, this->logoSprite.getLocalBounds().height / 2.0f);
    this->logoSprite.scale(0.25f, 0.25f);
    this->logoSprite.move(0.0f, -60.0f);
    this->textEntity.addDrawable(this->logoSprite);

    this->textEntity.setPosition(this->tWindow.getSizeInWorld()/2.0f);
    tLayer.addDynamicEntity(this->textEntity);
    this->tWorld.addLayer(0, tLayer);

}

void TitleState::update(const sf::Time &tslu) {

    BaseState::update(tslu);

    fadeTimer += tslu.asMilliseconds();
    if (fadeTimer >= FADE_DELAY) {

        if (this->fadeIn)
            this->fadeAlpha += FADE_RATE;
        else
            this->fadeAlpha -= FADE_RATE;
        if (this->fadeAlpha > 255) {

            this->fadeAlpha = 255;
            this->fadeIn = false;

        }
        if (this->fadeAlpha < 0) {

            this->fadeAlpha = 0;
            this->fadeIn = true;

        }
        const sf::Color dcolor = this->developed.getFillColor();
        this->developed.setFillColor(sf::Color(dcolor.r, dcolor.g, dcolor.b, this->fadeAlpha));
        const sf::Color lcolor = this->logoSprite.getColor();
        this->logoSprite.setColor(sf::Color(lcolor.r, lcolor.g, lcolor.b, this->fadeAlpha));
        fadeTimer = 0;

    }

}
