//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"AnimatedSprite.hpp"

namespace sg {

    AnimatedSprite::AnimatedSprite() :
    sf::Sprite()
    {

        this->frameDelay = 0.0f;
        this->frameIndex = 0;
        this->timePast = 0.0f;
        this->playing = false;

    }

    AnimatedSprite::AnimatedSprite(float fd) :
    sf::Sprite()
    {

        this->frameDelay = fd;
        this->frameIndex = 0;
        this->timePast = 0.0f;
        this->playing = false;

    }

    AnimatedSprite::AnimatedSprite(float fd, const sf::Texture &t) :
    sf::Sprite(t)
    {

        this->frameDelay = fd;
        this->frameIndex = 0;
        this->timePast = 0.0f;
        this->playing = false;

    }

    AnimatedSprite::~AnimatedSprite() {

        this->rects.clear();
        this->surfaces.clear();
        this->frameDelay = 0.0f;
        this->frameIndex = 0;
        this->timePast = 0.0f;
        this->playing = false;

    }

    std::vector<sf::IntRect>::size_type AnimatedSprite::getNumOfFrames() const {

        return this->rects.size();

    }

    const BoundingShape *AnimatedSprite::getFrameBound(uint32_t idx) const {

        if (idx >= this->getNumOfFrames())
            return NULL;
        return this->surfaces[idx];

    }

    const sf::IntRect &AnimatedSprite::getFrameRect(uint32_t idx) const {

        if (idx >= this->getNumOfFrames())
            throw std::out_of_range ("getFrameRect(): Not a vaild rect index.");
        return this->rects[idx];

    }

    float AnimatedSprite::getFrameDelay() const {

        return this->frameDelay;

    }

    void AnimatedSprite::setFrameDelay(float fd) {

        this->frameDelay = fd;

    }

    uint32_t AnimatedSprite::getFrameIndex() const {

        return this->frameIndex;

    }

    float AnimatedSprite::getTimePast() const {

        return this->timePast;

    }

    bool AnimatedSprite::getIsPlaying() const {

        return this->playing;

    }

    std::vector<sf::IntRect>::size_type AnimatedSprite::addFrame(const sf::IntRect &newRect, const BoundingShape &bs) {

        this->rects.push_back(newRect);
        this->surfaces.push_back(&bs);
        return (this->getNumOfFrames() - 1);

    }

    std::pair<sf::IntRect &, const BoundingShape *> AnimatedSprite::removeFrame(uint32_t idx) {

        if (idx >= this->getNumOfFrames())
            throw std::out_of_range("removeFrame(): Not a vaild index.");

        sf::IntRect *r = &this->rects[idx];
        const BoundingShape *bs = this->surfaces[idx];
        this->rects.erase(this->rects.begin() + idx);
        this->surfaces.erase(this->surfaces.begin() + idx);

        return std::pair<sf::IntRect &, const BoundingShape *>((*r), bs);

    }

    void AnimatedSprite::start() {

        this->playing = true;

    }

    void AnimatedSprite::stop() {

        this->playing = false;

    }

    void AnimatedSprite::restart() {

        this->frameIndex = 0;
        this->timePast = 0.0;
        this->playing = true;

    }

    void AnimatedSprite::update(float tslu) {

        if (!this->playing || this->getNumOfFrames() <= 0)
            return;

        this->timePast += tslu;
        if (this->timePast >= this->frameDelay) {

            this->timePast = 0.0;
            this->frameIndex = ((this->frameIndex + 1) % this->getNumOfFrames());
            this->setTextureRect(this->rects[this->frameIndex]);

        }

    }

}
