#pragma once

//C++ includes
#include<iostream>
#include<vector>
#include<math.h>
#include<stdint.h>

//SFML includes
#include<SFML/Graphics.hpp>

//SHOGUN includes
#include"AnimatedSprite.hpp"
#include"../management/GameLoop.hpp"

namespace sg {

    typedef struct {

        sf::Drawable *d;
        sf::Transformable *t;

    } Component;

    class Entity: public sf::Transformable {

        private:
            void expandSurfaceBounds(sf::FloatRect &, sf::FloatRect) const;
            bool deletion;

        protected:
            std::vector<Component *> components;
            bool isCollidable;
            virtual void handleCollision(Entity &, const std::vector<sf::Vector2f> &) {}
            virtual void render() {

                // render sprites
                for (std::vector<Component *>::iterator it = this->components.begin() ; it != this->components.end(); ++it)
                    GameLoop::inst().getRenderWindow().draw(*((*it)->d));

            }

        public:
            Entity();
            Entity(bool);
            ~Entity();
            bool collides(sg::Entity &);// calls handleCollision
            bool getIsCollidable() const;
            void setIsCollidable(bool);
            bool getDeletionStatus();
            void setDeletionStatus(bool);
            std::vector<Component *>::size_type getNumOfComponents() const;
            const Component *getComponent(uint32_t) const;
            void setOriginComponent(uint32_t, const sf::Vector2f &);
            void setPositionComponent(uint32_t, const sf::Vector2f &);
            void moveComponent(uint32_t, const sf::Vector2f &);
            void setRotationComponent(uint32_t, float, bool=true);
            void rotateComponent(uint32_t, float, bool=true);
            void setScaleComponent(uint32_t, const sf::Vector2f &);
            void scaleComponent(uint32_t, const sf::Vector2f &);
            sf::FloatRect getSurfaceBounds(bool=true) const;
            sf::FloatRect getTextureBounds(bool=true) const;
            std::vector<Component *>::size_type addComponent(Component &);
            Component *removeComponent(uint32_t);
            virtual void update(sf::Time tslu) {

                for (std::vector<Component *>::iterator it = this->components.begin() ; it != this->components.end(); ++it)
                    if (AnimatedSprite *s = dynamic_cast<AnimatedSprite *>((*it)->t))
                        s->update(tslu);

            }
            void draw();

    };

}
