#pragma once

//C++ includes
#include<vector>
#include<utility>
#include<stdint.h>

//SFML includes
#include<SFML/Graphics.hpp>

//Shogun includes
#include"BoundingShape.hpp"

namespace sg {

    class AnimatedSprite : public sf::Sprite {

        private:
            std::vector<sf::IntRect> rects;
            std::vector<const BoundingShape *> surfaces;
            float frameDelay;
            uint32_t frameIndex;
            float timePast;
            bool playing;

        public:
            AnimatedSprite();
            AnimatedSprite(float);
            AnimatedSprite(float, const sf::Texture &);
            ~AnimatedSprite();
            std::vector<sf::IntRect>::size_type getNumOfFrames() const;
            const BoundingShape *getFrameBound(uint32_t) const;
            const sf::IntRect &getFrameRect(uint32_t) const;
            float getFrameDelay() const;
            void setFrameDelay(float);
            uint32_t getFrameIndex() const;
            float getTimePast() const;
            bool getIsPlaying() const;
            std::vector<sf::IntRect>::size_type addFrame(const sf::IntRect &, const BoundingShape &);
            std::pair<sf::IntRect &, const BoundingShape *> removeFrame(uint32_t);
            void start();
            void stop();
            void restart();
            void update(float);
            void setRotation(float angle);
            void rotate(float angle);
            void setScale(float, float);
            void scale(float, float);
            void setScale(const sf::Vector2f &);
            void scale(const sf::Vector2f &);

    };

}
