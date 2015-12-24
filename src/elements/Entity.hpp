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
#include"BoundedSprite.hpp"

namespace sg {

    class Entity {

        private:
           void expandSurfaceBounds(sf::FloatRect &, sf::FloatRect);

        protected:
            std::vector<sf::Sprite *> sprites;
            bool isCollidable;
            sf::Vector2f pos;//world coordinates
            virtual void handleCollision(Entity &, const std::vector<sf::Vector2f> &) {}

        public:
            Entity();
            Entity(const sf::Vector2f &, bool=true);
            ~Entity();
            bool collides(sg::Entity &);// calls handleCollision
            bool getIsCollidable() const;
            void setIsCollidable(bool);
            std::vector<sf::Sprite *>::size_type getNumOfSprites() const;
            const sf::Sprite *getSprite(uint32_t) const;
            void move(const sf::Vector2f &);
            void moveSprite(uint32_t, const sf::Vector2f &);
            void translate(const sf::Vector2f &);
            void translateSprite(uint32_t, const sf::Vector2f &);
            void rotate(float, bool=true);
            void rotateSprite(uint32_t, float, bool=true);
            void scale(const sf::Vector2f &);
            void scaleSprite(uint32_t, const sf::Vector2f &);
            const sf::Vector2f &getPos() const;
            const sf::Vector2f &getPosSprite(uint32_t) const;
            sf::FloatRect getSurfaceBounds();
            sf::FloatRect getTextureBounds();
            std::vector<sf::Sprite *>::size_type addSprite(sf::Sprite &);
            sf::Sprite *removeSprite(uint32_t);
            virtual void update(sf::Time tslu) {
        
                float tslu_sec = tslu.asSeconds();

                for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin() ; it != this->sprites.end(); ++it)
                    if (AnimatedSprite *s = dynamic_cast<AnimatedSprite *>((*it)))
                        s->update(tslu_sec);
        
            }
            virtual void draw() {
        
                //TODO: Uncomment this code once GameLoop is ready.
                /*for (std::vector<sf::Sprite *>::iterator it = this->sprites.begin() ; it != this->sprites.end(); ++it)
                    GameLoop.inst().getRenderWindow().draw((*it));*/
        
            }

    };

}
