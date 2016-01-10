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
#include"../management/GameLoop.hpp"

namespace sg {

    class Entity: public sf::Transformable {

        private:
            void expandSurfaceBounds(sf::FloatRect &, sf::FloatRect);
            bool deletion;

        protected:
            std::vector<sf::Drawable *> sprites;
            bool isCollidable;
            virtual void handleCollision(Entity &, const std::vector<sf::Vector2f> &) {}

        public:
            Entity();
            Entity(bool);
            ~Entity();
            bool collides(sg::Entity &);// calls handleCollision
            bool getIsCollidable() const;
            void setIsCollidable(bool);
            std::vector<sf::Drawable *>::size_type getNumOfSprites() const;
            const sf::Drawable *getSprite(uint32_t) const;
            void setOriginSprite(uint32_t, const sf::Vector2f &);
            void setPositionSprite(uint32_t, const sf::Vector2f &);
            void moveSprite(uint32_t, const sf::Vector2f &);
            void setRotationSprite(uint32_t, float, bool=true);
            void rotateSprite(uint32_t, float, bool=true);
            void setScaleSprite(uint32_t, const sf::Vector2f &);
            void scaleSprite(uint32_t, const sf::Vector2f &);
            sf::FloatRect getSurfaceBounds(bool=true);
            sf::FloatRect getTextureBounds(bool=true);
            std::vector<sf::Drawable *>::size_type addSprite(sf::Drawable &);
            sf::Drawable *removeSprite(uint32_t);
            void setDeletionStatus(bool);
            bool getDeletionStatus();
            virtual void update(sf::Time tslu) {

                for (std::vector<sf::Drawable *>::iterator it = this->sprites.begin() ; it != this->sprites.end(); ++it)
                    if (AnimatedSprite *s = dynamic_cast<AnimatedSprite *>((*it)))
                        s->update(tslu);
        
            }
            virtual void draw() {

                // Transform view to draw entity in the correct place
                sf::View saveView = GameLoop::inst().getRenderWindow().getView();
                sf::View drawView = saveView;
                drawView.setCenter(this->getInverseTransform().transformPoint(saveView.getCenter()));
                GameLoop::inst().getRenderWindow().setView(drawView);

                // Draw sprites
                for (std::vector<sf::Drawable *>::iterator it = this->sprites.begin() ; it != this->sprites.end(); ++it)
                    GameLoop::inst().getRenderWindow().draw(*(*it));

                // Set view back to the way it was before
                GameLoop::inst().getRenderWindow().setView(saveView);
        
            }

    };

}
