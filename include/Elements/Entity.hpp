#pragma once

//C++ includes
#include <iostream>
#include <vector>
#include <math.h>
#include <stdint.h>
#include <typeinfo>

//SFML includes
#include <SFML/Graphics.hpp>

//Shogun includes
#include <Shogun/Elements/AnimatedSprite.hpp>
#include <Shogun/Elements/BoundingShape.hpp>
#include <Shogun/Management/GameLoop.hpp>

namespace sg {

    class Component {

        public:
            sf::Drawable *d = NULL;
            sf::Transformable *t = NULL;
            Component() {
            }
            Component(sf::Drawable &d, sf::Transformable &t) {

                this->d = &d;
                this->t = &t;

            }

    };

    class Entity: public sf::Transformable {

        private:
            //Private member variables
            bool deletion;
            //Private member functions
            void expandSurfaceBounds(sf::FloatRect &, sf::FloatRect) const;

        protected:
            //Protected member variables
            std::vector<Component *> components;
            std::vector<Entity *> possessions;
            Entity *owner;
            bool isCollidable;
            //Protected member functions
            virtual void handleCollision(const Entity &e, const std::vector<sf::Vector2f> &collisionVectors) {}

        public:
            Entity();
            Entity(bool);
            ~Entity();
            bool collides(Entity &);// calls handleCollision
            bool getIsCollidable() const;
            void setIsCollidable(bool);
            bool getDeletionStatus();
            void setDeletionStatus(bool);
            std::vector<Component *>::size_type getNumOfComponents() const;
            std::pair<const sf::Drawable *, const sf::Transformable *>getComponent(uint32_t) const;
            std::vector<Entity *>::size_type getNumOfPossessions() const;
            const Entity *getPossession(uint32_t) const;
            const Entity *getOwner() const;
            std::pair<sf::Vector2f, float> getGlobalTransform(sf::Transform &) const;
            sf::Vector2f getGlobalPosition() const;
            float getGlobalRotation() const;
            sf::Vector2f getGlobalScale() const;
            void setGlobalPosition(float, float);
            void setGlobalPosition(const sf::Vector2f &);
            void moveGlobally(float, float, bool=true, bool=true);
            void moveGlobally(const sf::Vector2f &, bool=true, bool=true);
            void setGlobalRotation(float, bool=true);
            void rotateGlobally(float, bool=true);
            void setGlobalScale(float, float);
            void setGlobalScale(const sf::Vector2f &);
            void scaleGlobally(float, float);
            void scaleGlobally(const sf::Vector2f &);
            void setOriginComponent(uint32_t, const sf::Vector2f &);
            void setPositionComponent(uint32_t, const sf::Vector2f &);
            void moveComponent(uint32_t, const sf::Vector2f &);
            void setRotationComponent(uint32_t, float, bool=true);
            void rotateComponent(uint32_t, float, bool=true);
            void setScaleComponent(uint32_t, const sf::Vector2f &);
            void scaleComponent(uint32_t, const sf::Vector2f &);
            sf::FloatRect getSurfaceBounds(bool=true) const;
            sf::FloatRect getTextureBounds(bool=true) const;
            std::vector<Component *>::size_type addDrawable(sf::Drawable &, bool=true);
            std::vector<Component *>::size_type addTransformable(sf::Transformable &, bool=true);
            std::vector<Component *>::size_type addComponent(sf::Drawable &, sf::Transformable &);
            std::pair<sf::Drawable *, sf::Transformable *> removeComponent(uint32_t);
            std::vector<Entity *>::size_type addPossession(Entity &, bool=true);
            Entity *removePossession(uint32_t, bool=true);
            int removePossession(Entity &, bool=true);
            virtual void update(sf::Time tslu) {

                for (auto &it : this->components)
                    if (AnimatedSprite *s = dynamic_cast<AnimatedSprite *>(it->t))
                        s->update(tslu);

            }
            virtual void draw(sf::RenderStates states=sf::RenderStates::Default) {

                sf::Transform globalTransform;
                this->getGlobalTransform(globalTransform);
                states.transform *= globalTransform;

                // render sprites
                for (const auto &it : this->components)
                    if(it->d)
                        GameLoop::inst().getRenderWindow().draw(*it->d, states);

            }

    };

}
