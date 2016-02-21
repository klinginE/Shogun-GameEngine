#include <queue>
#include <stdlib.h>
#include <functional>

#include "GameWorld.hpp"
#include "../elements/Entity.hpp"
#include "GameLoop.hpp"

#include "GameWindow.hpp"

namespace sg {
    
    GameWindow::GameWindow() {
       
        this->world = NULL;

        this->positionInScreen.x = 0;
        this->positionInScreen.y = 0;
        this->sizeInScreen.x = 1;
        this->sizeInScreen.y = 1;
        this->positionInWorld.x = 0;
        this->positionInWorld.y = 0;
        this->sizeInWorld.x = GameLoop::inst().getRenderWindow().getSize().x;
        this->sizeInWorld.y = GameLoop::inst().getRenderWindow().getSize().y;
        this->rotationInWorld = 0;

        this->updateView();

        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return true;};
        
    }

    GameWindow::GameWindow(const GameWorld &world) {
    
        this->world = &world;
    
        this->positionInScreen.x = 0;
        this->positionInScreen.y = 0;
        this->sizeInScreen.x = 1;
        this->sizeInScreen.y = 1;
        this->positionInWorld.x = 0;
        this->positionInWorld.y = 0;
        this->sizeInWorld.x = GameLoop::inst().getRenderWindow().getSize().x;
        this->sizeInWorld.y = GameLoop::inst().getRenderWindow().getSize().y;
        this->rotationInWorld = 0;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return true;};

    }
    
    GameWindow::GameWindow(const GameWorld &world,
                           sf::Vector2f positionInScreen,
                           sf::Vector2f sizeInScreen,
                           sf::Vector2f positionInWorld,
                           sf::Vector2f sizeInWorld,
                           float rotationInWorld) {
        
        this->world = &world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = rotationInWorld;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return true;};

    }
    GameWindow::GameWindow(const GameWorld &world,
                           sf::Vector2f positionInScreen,
                           sf::Vector2f sizeInScreen,
                           sf::Vector2f positionInWorld,
                           sf::Vector2f sizeInWorld) {
        
        this->world = &world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return true;};

    }
    
    GameWindow::GameWindow(const GameWorld &world,
                           sf::Vector2f positionInWorld,
                           sf::Vector2f sizeInWorld,
                           float rotationInWorld) {
    
        this->world = &world;
    
        this->positionInScreen.x = 0;
        this->positionInScreen.y = 0;
        this->sizeInScreen.x = 1;
        this->sizeInScreen.y = 1;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return true;};

    }
    
    GameWindow::GameWindow(const GameWorld &world,
                           sf::Vector2f positionInScreen,
                           sf::Vector2f sizeInScreen) {
    
        this->world = &world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return true;};

    }

    void GameWindow::render() {

        if (world == NULL) return;

        auto entities = world->getEntities();
        
        auto comp = [=](Entity *e1, Entity *e2)->bool{return renderOrder(*e1, *e2);}; 

        std::priority_queue<Entity *, std::vector<Entity *>,
                            decltype(comp)> renderQueue(comp);
    
        for (auto entityIter=entities.begin();
            entityIter!=entities.end(); ++entityIter) {

            Entity *e = *entityIter;

            auto b = e->getTextureBounds(true);

            if (/*true ||*/ ((b.left <= this->getPosInWorld().x + this->getSizeInWorld().x/2)
            &&  (b.top <= this->getPosInWorld().y + this->getSizeInWorld().y/2)
            &&  (b.left + b.width >= this->getPosInWorld().x - this->getSizeInWorld().x/2)
            &&  (b.top + b.height >= this->getPosInWorld().y - this->getSizeInWorld().y/2))) {

                // add to render queue
                renderQueue.push(e);

            }

        }
       
        updateView();
        GameLoop::inst().getRenderWindow().setView(this->view);
        //GameLoop::inst().getRenderWindow().clear(sf::Color::Black);

        while (!renderQueue.empty()) {
    
            // fetch entity
            Entity *entity = renderQueue.top();
            renderQueue.pop();

            // draw entity
            entity->draw();

        }

        //GameLoop::inst().getRenderWindow().display();
        GameLoop::inst().getRenderWindow().setView(
                GameLoop::inst().getRenderWindow().getDefaultView());
    
    }
    
    void GameWindow::setWorld(const GameWorld &newWorld) {
        this->world = &newWorld;
    }
    const GameWorld *GameWindow::getWorld() {
        return this->world;
    }
    
    void GameWindow::setPosInScreen(sf::Vector2f positionInScreen) {
        this->positionInScreen = positionInScreen;
    }
    sf::Vector2f GameWindow::getPosInScreen() {
        return this->positionInScreen;
    }
    
    void GameWindow::setSizeInScreen(sf::Vector2f sizeInScreen) {
        this->sizeInScreen = sizeInScreen;
    }
    sf::Vector2f GameWindow::getSizeInScreen() {
        return this->sizeInScreen;
    }
    
    void GameWindow::setPosInWorld(sf::Vector2f posInWorld) {
        this->positionInWorld = posInWorld;
    }
    sf::Vector2f GameWindow::getPosInWorld() {
        return this->positionInWorld;
    }
    
    void GameWindow::setSizeInWorld(sf::Vector2f sizeInWorld) {
        this->sizeInWorld = sizeInWorld;
    }
    sf::Vector2f GameWindow::getSizeInWorld() {
        return this->sizeInWorld;
    }
    
    void GameWindow::setRotInWorld(float rotationInWorld) {
        this->rotationInWorld = rotationInWorld;
    }
    float GameWindow::getRotInWorld() {
        return this->rotationInWorld;
    }

    void GameWindow::setRenderOrder(std::function<bool(const Entity &, const Entity &)> newRenderOrder) {
        
        renderOrder = newRenderOrder;
    }
    
    void GameWindow::updateView() {
    
        sf::Rect<float> viewport(this->positionInScreen.x,
                                 this->positionInScreen.y,
                                 this->sizeInScreen.x,
                                 this->sizeInScreen.y);
        view.setViewport(viewport);
        view.setCenter(getPosInWorld());
        view.setSize(getSizeInWorld());
        view.setRotation(getRotInWorld());
    
    }
    
    sf::View &GameWindow::getView() {
        return view;
    }

}
