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

        //this->renderOrder = [=](const Entity &e1, const Entity &e2)->bool {return false;};

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

        //this->renderOrder = [=](const Entity &e1, const Entity &e2)->bool {return false;};

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

        //this->renderOrder = [=](const Entity &e1, const Entity &e2)->bool {return false;};

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

        //this->renderOrder = [=](const Entity &e1, const Entity &e2)->bool {return false;};

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

        //this->renderOrder = [=](const Entity &e1, const Entity &e2)->bool {return false;};

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

        //this->renderOrder = [=](const Entity &e1, const Entity &e2)->bool {return false;};

    }

    void GameWindow::render() {

        if (world == NULL)
            return;

        updateView();
        const sf::View v = GameLoop::inst().getRenderWindow().getView();
        GameLoop::inst().getRenderWindow().setView(this->view);
        //GameLoop::inst().getRenderWindow().clear(sf::Color::Black);

        auto layers = world->getLayers();

        //auto comp = [=](Entity *e1, Entity *e2)->bool{return renderOrder(*e1, *e2);};

        //std::priority_queue<Entity *, std::vector<Entity *>, decltype(comp)> renderQueue(comp);


        sf::FloatRect winBounds(this->getPosInWorld().x - this->getSizeInWorld().x / 2.0f, //left
                                this->getPosInWorld().y - this->getSizeInWorld().y / 2.0f, //top
                                this->getSizeInWorld().x,                                  //width
                                this->getSizeInWorld().y);                                 //height

        for (auto it = layers.begin(); it != layers.end(); ++it) {

            if (!it->second->renderStatus)
                continue;

            if (it->second->sortStatus) {

                std::function<bool(const Entity *, const Entity *)> ro = it->second->getRenderOrder();
                std::function<bool(const Entity *, const Entity *)> nro = [=](const Entity *e0, const Entity *e1)->bool {

                    sf::FloatRect b0 = e0->getTextureBounds(true);
                    sf::FloatRect b1 = e1->getTextureBounds(true);
                    bool e0InsideWindow = ((b0.left <= winBounds.left + winBounds.width) && (b0.top <= winBounds.top + winBounds.height) && (b0.left + b0.width >= winBounds.left) && (b0.top + b0.height >= winBounds.top));
                    bool e1InsideWindow = ((b1.left <= winBounds.left + winBounds.width) && (b1.top <= winBounds.top + winBounds.height) && (b1.left + b1.width >= winBounds.left) && (b1.top + b1.height >= winBounds.top));

                    if (!e0InsideWindow)
                        return false;
                    if (e0InsideWindow && !e1InsideWindow)
                        return true;

                    return ro(e0, e1);

                };
                it->second->sortRenderList(nro);
                it->second->sortStatus = false;

            }

            for (Entity *e : it->second->getRenderList()) {

                auto b = e->getTextureBounds(true);
                if ((b.left <= winBounds.left + winBounds.width) &&
                    (b.top <= winBounds.top + winBounds.height) &&
                    (b.left + b.width >= winBounds.left) &&
                    (b.top + b.height >= winBounds.top))
                    e->draw();
                else
                    break;

            }

        }

        //GameLoop::inst().getRenderWindow().display();
        GameLoop::inst().getRenderWindow().setView(v);

    }

    void GameWindow::setWorld(const GameWorld &newWorld) {

        this->world = &newWorld;
        auto layers = world->getLayers();
        for (auto it = layers.begin(); it != layers.end(); ++it)
            it->second->sortStatus = true;

    }

    const GameWorld *GameWindow::getWorld() const {

        return this->world;

    }

    void GameWindow::setPosInScreen(const sf::Vector2f &positionInScreen) {

        if (positionInScreen.x != this->positionInScreen.x ||
            positionInScreen.y != this->positionInScreen.y) {

            this->positionInScreen = positionInScreen;
            if (this->world) {

                auto layers = world->getLayers();
                for (auto it = layers.begin(); it != layers.end(); ++it)
                    it->second->sortStatus = true;

            }

        }

    }

    sf::Vector2f GameWindow::getPosInScreen() const {

        return this->positionInScreen;

    }

    void GameWindow::setSizeInScreen(const sf::Vector2f &sizeInScreen) {

        if (sizeInScreen.x != this->sizeInScreen.x ||
            sizeInScreen.y != this->sizeInScreen.y) {

            this->sizeInScreen = sizeInScreen;
            if (this->world) {

                auto layers = world->getLayers();
                for (auto it = layers.begin(); it != layers.end(); ++it)
                    it->second->sortStatus = true;

            }

        }

    }

    sf::Vector2f GameWindow::getSizeInScreen() const {

        return this->sizeInScreen;

    }

    void GameWindow::setPosInWorld(const sf::Vector2f &positionInWorld) {

        if (positionInWorld.x != this->positionInWorld.x ||
            positionInWorld.y != this->positionInWorld.y) {

            this->positionInWorld = positionInWorld;
            if (this->world) {

                auto layers = world->getLayers();
                for (auto it = layers.begin(); it != layers.end(); ++it)
                    it->second->sortStatus = true;

            }

        }

    }

    sf::Vector2f GameWindow::getPosInWorld() const {

        return this->positionInWorld;

    }

    void GameWindow::setSizeInWorld(const sf::Vector2f &sizeInWorld) {

        if (sizeInWorld.x != this->sizeInWorld.x ||
            sizeInWorld.y != this->sizeInWorld.y) {

            this->sizeInWorld = sizeInWorld;
            if (this->world) {

                auto layers = world->getLayers();
                for (auto it = layers.begin(); it != layers.end(); ++it)
                    it->second->sortStatus = true;

            }

        }

    }

    sf::Vector2f GameWindow::getSizeInWorld() const {

        return this->sizeInWorld;

    }

    void GameWindow::setRotInWorld(float rotationInWorld) {

        if (rotationInWorld != this->rotationInWorld) {

            this->rotationInWorld = rotationInWorld;
            if (this->world) {

                auto layers = world->getLayers();
                for (auto it = layers.begin(); it != layers.end(); ++it)
                    it->second->sortStatus = true;

            }

        }

    }

    float GameWindow::getRotInWorld() const {

        return this->rotationInWorld;

    }

    /*void GameWindow::setRenderOrder(std::function<bool(const Entity &, const Entity &)> newRenderOrder) {

        renderOrder = newRenderOrder;

    }*/

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
