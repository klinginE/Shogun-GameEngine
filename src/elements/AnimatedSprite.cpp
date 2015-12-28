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

    void AnimatedSprite::setRotation(float angle) {

        sf::Sprite::setRotation(angle);
        for (std::vector<const BoundingShape *>::const_iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            for (uint32_t i = 0; i <= (*it)->getNumOfShapes(); i++) {

                //This const cast is dangerous as it could have undefined behavior
                sf::Shape *curShape = const_cast<sf::Shape *>((*it)->getShape(i));
                const sf::Vector2f &temp = curShape->getOrigin();
                curShape->setOrigin(this->getOrigin());
                curShape->setRotation(angle);
                curShape->setOrigin(temp);

            }

    }

    void AnimatedSprite::rotate(float angle) {

        sf::Sprite::rotate(angle);
        for (std::vector<const BoundingShape *>::const_iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            for (uint32_t i = 0; i <= (*it)->getNumOfShapes(); i++) {

                //This const cast is dangerous as it could have undefined behavior
                sf::Shape *curShape = const_cast<sf::Shape *>((*it)->getShape(i));
                const sf::Vector2f temp = curShape->getOrigin();
                curShape->setOrigin(this->getOrigin());
                curShape->rotate(angle);
                curShape->setOrigin(temp);

            }

    }

    void AnimatedSprite::setScale(float factorX, float factorY) {

        sf::Sprite::setScale(factorX, factorY);
        for (std::vector<const BoundingShape *>::const_iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            for (uint32_t i = 0; i <= (*it)->getNumOfShapes(); i++) {

                //This const cast is dangerous as it could have undefined behavior
                sf::Shape *curShape = const_cast<sf::Shape *>((*it)->getShape(i));
                const sf::Vector2f temp = curShape->getOrigin();
                curShape->setOrigin(this->getOrigin());
                curShape->setScale(factorX, factorY);
                curShape->setOrigin(temp);

            }

    }

    void AnimatedSprite::scale(float factorX, float factorY) {

        sf::Sprite::scale(factorX, factorY);
        for (std::vector<const BoundingShape *>::const_iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            for (uint32_t i = 0; i <= (*it)->getNumOfShapes(); i++) {

                //This const cast is dangerous as it could have undefined behavior
                sf::Shape *curShape = const_cast<sf::Shape *>((*it)->getShape(i));
                const sf::Vector2f temp = curShape->getOrigin();
                curShape->setOrigin(this->getOrigin());
                curShape->scale(factorX, factorY);
                curShape->setOrigin(temp);

            }

    }

    void AnimatedSprite::setScale(const sf::Vector2f &factor) {

        sf::Sprite::setScale(factor);
        for (std::vector<const BoundingShape *>::const_iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            for (uint32_t i = 0; i <= (*it)->getNumOfShapes(); i++) {

                //This const cast is dangerous as it could have undefined behavior
                sf::Shape *curShape = const_cast<sf::Shape *>((*it)->getShape(i));
                const sf::Vector2f temp = curShape->getOrigin();
                curShape->setOrigin(this->getOrigin());
                curShape->setScale(factor);
                curShape->setOrigin(temp);

            }

    }

    void AnimatedSprite::scale(const sf::Vector2f &factor) {

        sf::Sprite::scale(factor);
        for (std::vector<const BoundingShape *>::const_iterator it = this->surfaces.begin(); it != this->surfaces.end(); ++it)
            for (uint32_t i = 0; i <= (*it)->getNumOfShapes(); i++) {

                //This const cast is dangerous as it could have undefined behavior
                sf::Shape *curShape = const_cast<sf::Shape *>((*it)->getShape(i));
                const sf::Vector2f temp = curShape->getOrigin();
                curShape->setOrigin(this->getOrigin());
                curShape->scale(factor);
                curShape->setOrigin(temp);

            }

    }

}
