#include <queue>

#include <Shogun/Elements/Entity.hpp>
#include <Shogun/Management/GameLoop.hpp>

#include <Shogun/Management/GameWindow.hpp>

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

        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return false;};
        
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
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return false;};

    }
    
    GameWindow::GameWindow(const GameWorld &world,
                           const sf::Vector2f &positionInScreen,
                           const sf::Vector2f &sizeInScreen,
                           const sf::Vector2f &positionInWorld,
                           const sf::Vector2f &sizeInWorld,
                           float rotationInWorld) {
        
        this->world = &world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = rotationInWorld;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return false;};

    }
    GameWindow::GameWindow(const GameWorld &world,
                           const sf::Vector2f &positionInScreen,
                           const sf::Vector2f &sizeInScreen,
                           const sf::Vector2f &positionInWorld,
                           const sf::Vector2f &sizeInWorld) {
        
        this->world = &world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return false;};

    }
    
    GameWindow::GameWindow(const GameWorld &world,
                           const sf::Vector2f &positionInWorld,
                           const sf::Vector2f &sizeInWorld,
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
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return false;};

    }
    
    GameWindow::GameWindow(const GameWorld &world,
                           const sf::Vector2f &positionInScreen,
                           const sf::Vector2f &sizeInScreen) {
    
        this->world = &world;
    
        this->positionInScreen = positionInScreen;
        this->sizeInScreen = sizeInScreen;
        this->positionInWorld = positionInWorld;
        this->sizeInWorld = sizeInWorld;
        this->rotationInWorld = 0;

        this->updateView();
        
        this->renderOrder = [=](const Entity &e1, const Entity &e2) -> bool {return false;};

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
    const GameWorld *GameWindow::getWorld() const {
        return this->world;
    }
    
    void GameWindow::setPosInScreen(const sf::Vector2f &positionInScreen) {
        this->positionInScreen = positionInScreen;
    }
    sf::Vector2f GameWindow::getPosInScreen() const {
        return this->positionInScreen;
    }
    
    void GameWindow::setSizeInScreen(const sf::Vector2f &sizeInScreen) {
        this->sizeInScreen = sizeInScreen;
    }
    sf::Vector2f GameWindow::getSizeInScreen() const {
        return this->sizeInScreen;
    }
    
    void GameWindow::setPosInWorld(const sf::Vector2f &posInWorld) {
        this->positionInWorld = posInWorld;
    }
    sf::Vector2f GameWindow::getPosInWorld() const {
        return this->positionInWorld;
    }
    
    void GameWindow::setSizeInWorld(const sf::Vector2f &sizeInWorld) {
        this->sizeInWorld = sizeInWorld;
    }
    sf::Vector2f GameWindow::getSizeInWorld() const {
        return this->sizeInWorld;
    }
    
    void GameWindow::setRotInWorld(float rotationInWorld) {
        this->rotationInWorld = rotationInWorld;
    }
    float GameWindow::getRotInWorld() const {
        return this->rotationInWorld;
    }

    void GameWindow::setRenderOrder(std::function<bool(const Entity &, const Entity &)> newRenderOrder) {
        
        renderOrder = newRenderOrder;
    }

    sf::Vector2f GameWindow::worldCoordToScreenCoord(sf::Vector2f worldCoord) const {
        sf::Vector2f coord = worldCoord - getPosInWorld();
        coord.x = coord.x*getSizeInScreen().x/getSizeInWorld().x;
        coord.y = coord.y*getSizeInScreen().y/getSizeInWorld().y;
        coord += getPosInScreen();
        return coord;
    }

    sf::Vector2f GameWindow::screenCoordToWorldCoord(sf::Vector2f screenCoord) const {
        sf::Vector2f coord = screenCoord - getPosInScreen();
        coord.x = coord.x*getSizeInWorld().x/getSizeInScreen().x;
        coord.y = coord.y*getSizeInWorld().y/getSizeInScreen().y;
        coord += getPosInWorld();
        return coord;
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
    
    const sf::View * GameWindow::getView() const {
        return &view;
    }

}
