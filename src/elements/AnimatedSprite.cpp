//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"AnimatedSprite.hpp"

namespace sg {

    AnimatedSprite::AnimatedSprite() :
    sf::Sprite()
    {

        this->frameDelay = sf::Time::Zero;
        this->timePast = sf::Time::Zero;
        this->frameIndex = 0;
        this->playing = false;

    }

    AnimatedSprite::AnimatedSprite(sf::Time fd) :
    sf::Sprite()
    {

        this->frameDelay = fd;
        this->timePast = sf::Time::Zero;
        this->frameIndex = 0;
        this->playing = false;

    }

    AnimatedSprite::AnimatedSprite(sf::Time fd, const sf::Texture &t) :
    sf::Sprite(t)
    {

        this->frameDelay = fd;
        this->timePast = sf::Time::Zero;
        this->frameIndex = 0;
        this->playing = false;

    }

    AnimatedSprite::~AnimatedSprite() {

        this->rects.clear();
        this->surfaces.clear();
        this->frameDelay = sf::Time::Zero;
        this->timePast = sf::Time::Zero;
        this->frameIndex = 0;
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
            throw std::out_of_range("getFrameRect(): Not a vaild rect index.");
        return this->rects[idx];

    }

    sf::Time AnimatedSprite::getFrameDelay() const {

        return this->frameDelay;

    }

    void AnimatedSprite::setFrameDelay(sf::Time fd) {

        this->frameDelay = fd;

    }

    uint32_t AnimatedSprite::getFrameIndex() const {

        return this->frameIndex;

    }

    sf::Time AnimatedSprite::getTimePast() const {

        return this->timePast;

    }

    bool AnimatedSprite::getIsPlaying() const {

        return this->playing;

    }

    std::vector<sf::IntRect>::size_type AnimatedSprite::addFrame(sf::IntRect &newRect, BoundingShape &bs) {

        this->rects.push_back(newRect);
        this->surfaces.push_back(&bs);
        return (this->getNumOfFrames() - 1);

    }

    std::pair<sf::IntRect &, BoundingShape *> AnimatedSprite::removeFrame(uint32_t idx) {

        if (idx >= this->getNumOfFrames())
            throw std::out_of_range("removeFrame(): Not a vaild index.");

        sf::IntRect *r = &this->rects[idx];
        BoundingShape *bs = this->surfaces[idx];
        this->rects.erase(this->rects.begin() + idx);
        this->surfaces.erase(this->surfaces.begin() + idx);

        return std::pair<sf::IntRect &, BoundingShape *>((*r), bs);

    }

    void AnimatedSprite::start() {

        this->playing = true;
        this->timePast = sf::Time::Zero;

    }

    void AnimatedSprite::stop() {

        this->playing = false;

    }

    void AnimatedSprite::restart() {

        this->frameIndex = 0;
        this->start();

    }

    void AnimatedSprite::update(sf::Time tslu) {

        if (!this->playing || this->getNumOfFrames() <= 0)
            return;

        this->timePast += tslu;
        if (this->timePast >= this->frameDelay) {

            this->timePast = sf::Time::Zero;
            this->frameIndex = ((this->frameIndex + 1) % this->getNumOfFrames());
            this->setTextureRect(this->rects[this->frameIndex]);

        }

    }

    void AnimatedSprite::setOrigin(float x, float y) {

        sf::Sprite::setOrigin(x, y);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setOrigin(sf::Vector2f(x, y));

    }

    void AnimatedSprite::setOrigin(const sf::Vector2f &origin) {

        sf::Sprite::setOrigin(origin);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setOrigin(origin);

    }

    void AnimatedSprite::setPosition(float x, float y) {

        sf::Sprite::setPosition(x, y);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setPosition(sf::Vector2f(x, y));

    }

    void AnimatedSprite::setPosition(const sf::Vector2f &position) {

        sf::Sprite::setPosition(position);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setPosition(position);

    }

    void AnimatedSprite::move(float offsetX, float offsetY) {

        sf::Sprite::move(offsetX, offsetY);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->move(sf::Vector2f(offsetX, offsetY));

    }

    void AnimatedSprite::move(const sf::Vector2f &offset) {

        sf::Sprite::move(offset);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->move(offset);

    }


    void AnimatedSprite::setRotation(float angle) {

        sf::Sprite::setRotation(angle);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setRotation(angle);

    }

    void AnimatedSprite::rotate(float angle) {

        sf::Sprite::rotate(angle);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->rotate(angle);

    }

    void AnimatedSprite::setScale(float factorX, float factorY) {

        sf::Sprite::setScale(factorX, factorY);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setScale(sf::Vector2f(factorX, factorY));

    }

    void AnimatedSprite::setScale(const sf::Vector2f &factor) {

        sf::Sprite::setScale(factor);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->setScale(factor);

    }

    void AnimatedSprite::scale(float factorX, float factorY) {

        sf::Sprite::scale(factorX, factorY);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->scale(sf::Vector2f(factorX, factorY));

    }

    void AnimatedSprite::scale(const sf::Vector2f &factor) {

        sf::Sprite::scale(factor);
        for (std::vector<BoundingShape *>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            (*it)->scale(factor);

    }

}
