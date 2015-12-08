#pragma once

//C++ includes
#include<vector>

//SFML includes
#include<SFML/Graphics.hpp>

//Shogun includes
#include"BoundingShape.hpp"

namespace sg {

    class AnimatedSprite : public sf::Sprite {

        private:
            std::vector<sf::IntRct> rects;
            std::vector<const sf::BoundingShape *> surfaces;
            float frameDelay;
            uint32_t frameIndex;
            float timePast;
            bool playing;

        public:
            AnimatedSprite();
            AnimatedSprite(float);
            AnimatedSprite(float, const sf::Texture &);
            ~AnimatedSprite();
            std::vector<sf::IntRect>::size_type getNumOfFrames();
            const BoundingShape *getFrameBound(uint32_t) const;
            const sf::IntRect &getFrameRect(uint32_t) const;
            float getFrameDelay() const;
            void setFrameDelay(float);
            uint32_t getFrameIndex() const;
            float getTimePast() const;
            bool getIsPlaying() const;
            std::vector<sf::IntRect>::size_type addFrame(const sf::IntRect &, const BoundingShape &);
            bool removeFrame(uint32_t);
            void start();
            void stop();
            void restart();
            void update(float);

    };

}
