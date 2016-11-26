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

    }

    void GameWindow::render() {

        if (world == NULL)
            return;

        updateView();
        const sf::View v = GameLoop::inst().getRenderWindow().getView();
        GameLoop::inst().getRenderWindow().setView(this->view);

        sf::Rect<long> winBounds(static_cast<long>(this->getPosInWorld().x - this->getSizeInWorld().x / 2.0f), //left
                                 static_cast<long>(this->getPosInWorld().y - this->getSizeInWorld().y / 2.0f), //top
                                 static_cast<long>(this->getSizeInWorld().x),                                  //width
                                 static_cast<long>(this->getSizeInWorld().y));                                 //height

        auto layers = world->getLayers();
        for (auto &it : layers) {

            it.second->renderArea = winBounds;
            it.second->render();

        }

        GameLoop::inst().getRenderWindow().setView(v);

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

    void GameWindow::setPosInWorld(const sf::Vector2f &positionInWorld) {

        this->positionInWorld = positionInWorld;

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

    const sf::View *GameWindow::getView() const {

        return &view;

    }

}
