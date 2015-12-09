#include <queue>

#include "GameWorld.hpp"
#include "../elements/Entity.hpp"
#include "GameLoop.hpp"

#include "GameWindow.hpp"

namespace sg {
    
    GameWindow::GameWindow(GameWorld *world) {
    
        this->world = world;
    
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
    }
    
    GameWindow::GameWindow(GameWorld *world,
                           sf::Vector2f positionInScreen,
                           sf::Vector2f sizeInScreen,
                           sf::Vector2f positionInWorld,
                           sf::Vector2f sizeInWorld,
                           float rotationInWorld) {
        
        this->world = world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = rotationInWorld;
    
        this->updateView();
    }
    GameWindow::GameWindow(GameWorld *world,
                           sf::Vector2f positionInScreen,
                           sf::Vector2f sizeInScreen,
                           sf::Vector2f positionInWorld,
                           sf::Vector2f sizeInWorld) {
        
        this->world = world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;
    
        this->updateView();
    }
    
    GameWindow::GameWindow(GameWorld *world,
                           sf::Vector2f positionInWorld,
                           sf::Vector2f sizeInWorld,
                           float rotationInWorld) {
    
        this->world = world;
    
        this->positionInScreen.x = 0;
        this->positionInScreen.y = 0;
        this->sizeInScreen.x = 1;
        this->sizeInScreen.y = 1;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;
    
        this->updateView();
    }
    
    GameWindow::GameWindow(GameWorld *world,
                           sf::Vector2f positionInScreen,
                           sf::Vector2f sizeInScreen) {
    
        this->world = world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;
    
        this->updateView();
    }

    class verticalComparitor {
        public:
            bool operator() (Entity *e1, Entity *e2) {
                if (e1->getPos().y < e2->getPos().y)
                    return true;
                else
                    return false;
            }
    };

    void GameWindow::render() {

        auto entities = world->getEntities();
        
        std::priority_queue<Entity, std::vector<Entity>,
                            verticalComparitor> renderQueue;
    
        for (auto entityIter=entities.begin();
            entityIter!=entities.end(); ++entityIter) {

            Entity *e = *entityIter;

            // TODO: check this logic with Eric

            auto left = e->getPos().x
                      + e->getSprite()->getGlobalBounds().left;
            auto top = e->getPos().y
                     + e->getSprite()->getGlobalBounds().top;
            auto width = e->getSprite()->getGlobalBounds().width;
            auto height = e->getSprite()->getGlobalBounds().height;
            auto right = left + width;
            auto bottom = top + height;

            if ((left <= this->positionInWorld.x + this->sizeInWorld.x)
            &&  (top <= this->positionInWorld.y + this->sizeInWorld.y)
            &&  (right >= this->positionInWorld.x)
            &&  (bottom >= this->positionInWorld.y)) {

                // add to render queue
                renderQueue.push(e);

            }

        }
        
        GameLoop::inst().getRenderWindow().setView(this->view);

        while (!renderQueue.empty()) {
    
            // fetch entity
            Entity *entity = entityQueue.top();
            entityQueue.pop();

            // draw entity
            entity->draw();

        }

        GameLoop::inst().getRenderWindow().setView(
                GameLoop::inst().getRenderWindow().getDefaultView());
    
    }
    
    void GameWindow::setWorld(GameWorld *newWorld) {
        this->world = newWorld;
    }
    GameWorld *GameWindow::getWorld() {
        return this->world;
    }
    
    void GameWindow::setPosInScreen(sf::Vector2f positionInScreen) {
    
        this->positionInScreen = positionInScreen;
        sf::Rect viewport(this->positionInScreen.x,
                          this->positionInScreen.y,
                          this->sizeInScreen.x,
                          this->sizeInScreen.y);
        view.setViewport(viewport);
    }
    sf::Vector2f GameWindow::getPosInScreen() {
        return this->positionInScreen;
    }
    
    void GameWindow::setSizeInScreen(sf::Vector2f sizeInScreen) {
        this->sizeInScreen = sizeInScreen;
        sf::Rect viewport(this->positionInScreen.x,
                          this->positionInScreen.y,
                          this->sizeInScreen.x,
                          this->sizeInScreen.y);
        view.setViewport(viewport);
    }
    sf::Vector2f GameWindow::getSizeInScreen() {
        return this->sizeInScreen;
    }
    
    void GameWindow::setPosInWorld(sf::Vector2f posInWorld) {
        this->positionInWorld = posInWorld;
        view.setCenter(posInWorld);
    }
    sf::Vector2f GameWindow::getPosInWorld() {
        return this->positionInWorld;
    }
    
    void GameWindow::setSizeInWorld(sf::Vector2f sizeInWorld) {
        this->sizeInWorld = sizeInWorld;
        view.setSize(sizeInWorld);
    }
    sf::Vector2f GameWindow::getSizeInWorld() {
        return this->sizeInWorld;
    }
    
    void GameWindow::setRotInWorld(float rotationInWorld) {
        this->rotationInWorld = rotationInWorld;
        view.setRotation(rotationInWorld);
    }
    float GameWindow::getRotInWorld() {
        return this->rotationInWorld;
    }
    
    void GameWindow::updateView() {
    
        sf::Rect viewport(this->positionInScreen.x,
                          this->positionInScreen.y,
                          this->sizeInScreen.x,
                          this->sizeInScreen.y);
        view.setViewport(viewport);
        view.setCenter(positionInWorld);
        view.setSize(sizeInWorld);
        view.setRotation(rotationInWorld);
    
    }
    
    bool GameWindow::verticalSort(Entity *e1, Entity *e2) {
        if (e1->getPos().y < e2->getPos().y)
            return true;
        else
            return false;
    }

}
