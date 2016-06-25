#pragma once

//C++ Includes
#include <map>

//Shogun Includes
#include <Shogun/Management/Layer.hpp>

namespace sg {

    class GameWorld {

        protected:
            std::map<uint32_t, Layer *> layers;

        public:
            GameWorld() {}
            GameWorld(std::map<uint32_t, Layer *>);
            virtual ~GameWorld() {}

            virtual void update(const sf::Time &);

            void addLayer(uint32_t, Layer &);
            void removeLayer(uint32_t);
            const Layer *getLayer(uint32_t) const;
            const std::map<uint32_t, Layer *> &getLayers() const;

    };

}
