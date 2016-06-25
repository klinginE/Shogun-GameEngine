#include <Shogun/Management/GameWorld.hpp>

namespace sg {

    // CONSTRUCTORS
    GameWorld::GameWorld(std::map<uint32_t, Layer *> ls) {

        this->layers = ls;

    }

    void GameWorld::update(const sf::Time &tslu) {

        for (auto it = layers.begin(); it != layers.end(); ++it)
            it->second->update(tslu);

    }

    void GameWorld::addLayer(uint32_t level, Layer &l) {

        layers[level] = &l;

    }

    void GameWorld::removeLayer(uint32_t level) {

        layers.erase(level);

    }

    const Layer *GameWorld::getLayer(uint32_t level) const {

        return layers.at(level);

    }

    const std::map<uint32_t, Layer *> &GameWorld::getLayers() const {

        return layers;

    }

}
