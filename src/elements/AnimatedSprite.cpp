//C++ includes
#include<stdexcept>

//SHOGUN includes
#include"AnimatedSprite.hpp"
#include"Entity.hpp"

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

    std::vector<sf::IntRect *>::size_type AnimatedSprite::getNumOfFrames() const {

        return this->rects.size();

    }

    const sf::Transformable *AnimatedSprite::getFrameBound(uint32_t idx) const {

        if (idx >= this->getNumOfFrames())
            return NULL;
        return this->surfaces[idx];

    }

    const sf::IntRect *AnimatedSprite::getFrameRect(uint32_t idx) const {

        if (idx >= this->getNumOfFrames())
            return NULL;
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

    std::vector<sf::IntRect *>::size_type AnimatedSprite::addFrame(sf::IntRect &newRect, sf::Transformable &newTrans) {

        if (dynamic_cast<Entity *>(&newTrans))
            throw std::invalid_argument("sf::Transfromable cannot be an Entity");
        if (dynamic_cast<AnimatedSprite *>(&newTrans))
            throw std::invalid_argument("sf::Transfromable cannot be an animatedSprite");

        newTrans.setOrigin(this->getOrigin());
        newTrans.setPosition(this->getPosition());
        newTrans.setRotation(this->getRotation());
        newTrans.setScale(this->getScale());

        this->rects.push_back(&newRect);
        this->surfaces.push_back(&newTrans);

        return (this->getNumOfFrames() - 1);

    }

    std::pair<sf::IntRect *, sf::Transformable *> AnimatedSprite::removeFrame(uint32_t idx) {

        if (idx >= this->getNumOfFrames())
            return std::pair<sf::IntRect *, sf::Transformable *>(NULL, NULL);

        sf::IntRect *r = this->rects[idx];
        sf::Transformable *t = this->surfaces[idx];
        this->rects.erase(this->rects.begin() + idx);
        this->surfaces.erase(this->surfaces.begin() + idx);

        return std::pair<sf::IntRect *, sf::Transformable *>(r, t);

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
        float timePastAsSec = this->timePast.asSeconds();
        float frameDelayAsSec = this->frameDelay.asSeconds();
        uint32_t steps = static_cast<uint32_t>(floor(timePastAsSec / frameDelayAsSec));
        this->timePast = sf::seconds(fmod(timePastAsSec, frameDelayAsSec));
        this->frameIndex = ((this->frameIndex + steps) % this->getNumOfFrames());
        this->setTextureRect((*(this->rects[this->frameIndex])));

    }

    void AnimatedSprite::setOrigin(float x, float y) {

        this->setOrigin(sf::Vector2f(x, y));

    }

    void AnimatedSprite::setOrigin(const sf::Vector2f &origin) {

        sf::Sprite::setOrigin(origin);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->setOrigin(origin);

    }

    void AnimatedSprite::setPosition(float x, float y) {

        this->setPosition(sf::Vector2f(x, y));

    }

    void AnimatedSprite::setPosition(const sf::Vector2f &position) {

        sf::Sprite::setPosition(position);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->setPosition(position);

    }

    void AnimatedSprite::move(float offsetX, float offsetY) {

        this->move(sf::Vector2f(offsetX, offsetY));

    }

    void AnimatedSprite::move(const sf::Vector2f &offset) {

        sf::Sprite::move(offset);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->move(offset);

    }


    void AnimatedSprite::setRotation(float angle) {

        sf::Sprite::setRotation(angle);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->setRotation(angle);

    }

    void AnimatedSprite::rotate(float angle) {

        sf::Sprite::rotate(angle);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->rotate(angle);

    }

    void AnimatedSprite::setScale(float factorX, float factorY) {

        this->setScale(sf::Vector2f(factorX, factorY));

    }

    void AnimatedSprite::setScale(const sf::Vector2f &factor) {

        sf::Sprite::setScale(factor);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->setScale(factor);

    }

    void AnimatedSprite::scale(float factorX, float factorY) {

        this->scale(sf::Vector2f(factorX, factorY));

    }

    void AnimatedSprite::scale(const sf::Vector2f &factor) {

        sf::Sprite::scale(factor);
        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < surfaces.size(); ++i)
            this->surfaces[i]->scale(factor);

    }

}
