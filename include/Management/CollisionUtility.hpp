#pragma once

//SFML includes
#include <SFML/Graphics.hpp>

namespace sg
{
    class CollisionUtility
	  {
        public:
            static CollisionUtility &inst();
            bool collides(const sf::Transformable &,
                          const sf::Transformable &,
                          const sf::Transform &,
                          const sf::Transform &,
                          sf::Vector2f &) const;

        private:
            bool circleIsElipse(const sf::CircleShape &circle, const sf::Transform &globalTrans) const;
            const sf::ConvexShape approximateCircle(const sf::CircleShape &circle) const;
            const sf::Shape *shapeOfTransformable(const sf::Transformable &transformable) const;
            sf::Vector2f calculateUnitNormal(const sf::Shape &,
                                             uint32_t,
                                             const sf::Transform &) const;
            float projectPoint(const sf::Shape &,
                               const sf::Vector2f &,
                               uint32_t,
                               const sf::Transform &) const;
            bool collides_ptp(const sf::Shape *,
                              const sf::Shape *,
                              const sf::Transform &,
                              const sf::Transform &,
                              sf::Vector2f &) const;
            bool collides_ctp(const sf::CircleShape *,
                              const sf::Shape *,
                              const sf::Transform &,
                              const sf::Transform &,
                              sf::Vector2f &) const;
            bool collides_ctc(const sf::CircleShape *,
                              const sf::CircleShape *,
                              const sf::Transform &,
                              const sf::Transform &,
                              sf::Vector2f &) const;

            CollisionUtility() {}
            CollisionUtility(CollisionUtility const&) = delete;
            void operator=(CollisionUtility const&) = delete;
    };
}