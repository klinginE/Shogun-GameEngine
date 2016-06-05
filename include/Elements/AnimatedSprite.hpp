#pragma once

//C++ includes
#include<vector>
#include<utility>
#include<stdint.h>

//SFML includes
#include<SFML/Graphics.hpp>

namespace sg {

    class AnimatedSprite : public sf::Sprite {

        private:
            std::vector<sf::IntRect *> rects;
            std::vector<sf::Transformable *> surfaces;
            sf::Time frameDelay;
            sf::Time timePast;
            uint32_t frameIndex;
            bool playing;

        public:
            AnimatedSprite();
            AnimatedSprite(sf::Time);
            AnimatedSprite(sf::Time, const sf::Texture &);
            std::vector<sf::IntRect>::size_type getNumOfFrames() const;
            const sf::Transformable *getFrameBound(uint32_t) const;
            const sf::IntRect *getFrameRect(uint32_t) const;
            sf::Time getFrameDelay() const;
            void setFrameDelay(sf::Time);
            uint32_t getFrameIndex() const;
            sf::Time getTimePast() const;
            void setTimePast(sf::Time);
            bool getIsPlaying() const;
            std::vector<sf::IntRect *>::size_type addFrame(sf::IntRect &, sf::Transformable &);
            std::pair<sf::IntRect *, sf::Transformable *> removeFrame(uint32_t);
            void start();
            void stop();
            void restart();
            void update(sf::Time);
            void setOrigin(float, float);
            void setOrigin(const sf::Vector2f &);
            void setPosition(float, float);
            void setPosition(const sf::Vector2f &);
            void move(float, float);
            void move(const sf::Vector2f &);
            void setRotation(float);
            void rotate(float);
            void setScale(float, float);
            void setScale(const sf::Vector2f &);
            void scale(float, float);
            void scale(const sf::Vector2f &);

    };

}
