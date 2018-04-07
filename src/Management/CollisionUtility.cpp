//C++ includes
#include <stdexcept>
#include <typeinfo>
#include <math.h>
#include <limits>
// #include <iostream>

//Shogun includes
#include <Shogun/Management/CollisionUtility.hpp>

namespace sg
{
    CollisionUtility &CollisionUtility::inst()
    {
        static CollisionUtility instance;

        return instance;
    }

    bool CollisionUtility::circleIsElipse(const sf::CircleShape &circle, const sf::Transform &globalTrans) const
    {
        bool isElipse = false;

        sf::Vector2f p0 = globalTrans.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(2.0f * circle.getRadius(), circle.getRadius())));
        sf::Vector2f p1 = globalTrans.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(circle.getRadius(), 2.0f * circle.getRadius())));
        sf::Vector2f center = globalTrans.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(circle.getRadius(), circle.getRadius())));
        p0 -= center;
        p1 -= center;
        float transRadius0 = std::round(std::sqrt(p0.x * p0.x + p0.y * p0.y));
        float transRadius1 = std::round(std::sqrt(p1.x * p1.x + p1.y * p1.y));

        if (transRadius0 <  transRadius1 || transRadius0 > transRadius1)
        {
            isElipse = true;
        }

        return isElipse;
    }

    const sf::Shape *CollisionUtility::shapeOfTransformable(const sf::Transformable &transformable) const
    {
        sf::Shape *shape = NULL;

        if (const sf::Shape *tempShape = dynamic_cast<const sf::Shape *>(&transformable))
        {
            // std::cout << "Found Shape!" << std::endl;
            if (const sf::CircleShape *tempCircleShape = dynamic_cast<const sf::CircleShape *>(tempShape))
            {
                shape = new sf::CircleShape(tempCircleShape->getRadius(), tempCircleShape->getPointCount());
                // std::cout << "Found Cricle Shape! " << shape << std::endl;
                shape->setOrigin(tempCircleShape->getOrigin());
                shape->setPosition(tempCircleShape->getPosition());
                shape->setRotation(tempCircleShape->getRotation());
                shape->setScale(tempCircleShape->getScale());
            }
            else if (const sf::ConvexShape *tempConvexShape = dynamic_cast<const sf::ConvexShape *>(tempShape))
            {
                shape = new sf::ConvexShape(tempConvexShape->getPointCount());
                // std::cout << "Found Convex Shape! " << shape << std::endl;
                shape->setOrigin(tempConvexShape->getOrigin());
                shape->setPosition(tempConvexShape->getPosition());
                shape->setRotation(tempConvexShape->getRotation());
                shape->setScale(tempConvexShape->getScale());
                for (uint32_t pi = 0; pi < tempConvexShape->getPointCount(); ++pi)
                {
                    ((sf::ConvexShape *)shape)->setPoint(pi, tempConvexShape->getPoint(pi));
                }
            }
            else if (const sf::RectangleShape *tempRectangleShape = dynamic_cast<const sf::RectangleShape *>(tempShape))
            {
                shape = new sf::RectangleShape(tempRectangleShape->getSize());
                // std::cout << "Found RectangleShape Shape! " << shape << std::endl;
                shape->setOrigin(tempRectangleShape->getOrigin());
                shape->setPosition(tempRectangleShape->getPosition());
                shape->setRotation(tempRectangleShape->getRotation());
                shape->setScale(tempRectangleShape->getScale());
            }
        }
        else if (const sf::Sprite *tempSprite = dynamic_cast<const sf::Sprite *>(&transformable))
        {
            sf::FloatRect bounds = tempSprite->getLocalBounds();

            shape= new sf::ConvexShape(4);
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(0, sf::Vector2f(bounds.left, bounds.top));
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(1, sf::Vector2f(bounds.left + bounds.width, bounds.top));
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(2, sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height));
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(3, sf::Vector2f(bounds.left, bounds.top + bounds.height));
            shape->setOrigin(tempSprite->getOrigin());
            shape->setPosition(tempSprite->getPosition());
            shape->setRotation(tempSprite->getRotation());
            shape->setScale(tempSprite->getScale());
        }
        else if (const sf::Text *tempText = dynamic_cast<const sf::Text *>(&transformable))
        {
            sf::FloatRect bounds = tempText->getLocalBounds();

            shape= new sf::ConvexShape(4);
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(0, sf::Vector2f(bounds.left, bounds.top));
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(1, sf::Vector2f(bounds.left + bounds.width, bounds.top));
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(2, sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height));
            dynamic_cast<sf::ConvexShape *>(shape)->setPoint(3, sf::Vector2f(bounds.left, bounds.top + bounds.height));
            shape->setOrigin(tempText->getOrigin());
            shape->setPosition(tempText->getPosition());
            shape->setRotation(tempText->getRotation());
            shape->setScale(tempText->getScale());
        }

        return shape;
    }

    const sf::ConvexShape CollisionUtility::approximateCircle(const sf::CircleShape &circle,
                                                              const sf::Transform &globalTrans) const
    {
        sf::FloatRect gb = globalTrans.transformRect(circle.getGlobalBounds());
        uint32_t n = static_cast<uint32_t>(ceil(std::min(gb.width, gb.height))) + 30;
        sf::ConvexShape approxCircle(n);
        float mult = 2.0f * M_PI / n - M_PI / 2.0f;
        for (uint32_t i = 0; i < n; ++i)
        {
            float angle = i * mult;
            sf::Vector2f v(std::cos(angle) * circle.getRadius(),
                           std::sin(angle) * circle.getRadius());
            v += sf::Vector2f(circle.getRadius(), circle.getRadius());
            approxCircle.setPoint(i, v);
        }
        approxCircle.setOrigin(circle.getOrigin());
        approxCircle.setPosition(circle.getPosition());
        approxCircle.setRotation(circle.getRotation());
        approxCircle.setScale(circle.getScale());

        return approxCircle;
    }

    sf::Vector2f CollisionUtility::calculateUnitNormal(const sf::Shape &poly,
                                                       uint32_t i,
                                                       const sf::Transform &globalTrans) const
    {
        uint32_t j = (i + 1) % poly.getPointCount();
        sf::Vector2f currentVertex = globalTrans.transformPoint(poly.getTransform().transformPoint(poly.getPoint(i)));
        sf::Vector2f adjacentVertex = globalTrans.transformPoint(poly.getTransform().transformPoint(poly.getPoint(j)));
        sf::Vector2f unitNormal(adjacentVertex.x - currentVertex.x, adjacentVertex.y - currentVertex.y);
        float magnitude = static_cast<float>(sqrt(unitNormal.x * unitNormal.x + unitNormal.y * unitNormal.y));
        unitNormal.x /= magnitude;
        unitNormal.y /= magnitude;
        //Rotate by 90
        float tempX = unitNormal.x;
        unitNormal.x = -1.0f * unitNormal.y;
        unitNormal.y = tempX;

        return unitNormal;
    }

    float CollisionUtility::projectPoint(const sf::Shape &poly,
                                         const sf::Vector2f &unitNormal,
                                         uint32_t k,
                                         const sf::Transform &globalTrans) const
    {
        sf::Vector2f vertex = globalTrans.transformPoint(poly.getTransform().transformPoint(poly.getPoint(k)));
        float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;

        return point;
    }

    bool CollisionUtility::collides_ptp(const sf::Shape *poly0,
                                        const sf::Shape *poly1,
                                        const sf::Transform &globalTrans0,
                                        const sf::Transform &globalTrans1,
                                        sf::Vector2f &collisionVector) const
    {
        // std::cout << "Begin ptp" << std::endl;
        // std::cout << "got poly0: " << poly0 << " got poly1: " << poly1 << std::endl;

        if (poly0 != NULL && poly1 != NULL)
        {
            sf::FloatRect bounds0 = poly0->getGlobalBounds();
            bounds0 = globalTrans0.transformRect(bounds0);
            bounds0.width += bounds0.left;
            bounds0.height += bounds0.top;

            sf::FloatRect bounds1 = poly1->getGlobalBounds();
            bounds1 = globalTrans1.transformRect(bounds1);
            bounds1.width += bounds0.left;
            bounds1.height += bounds1.top;

            if (bounds0.left <= bounds1.width &&
                bounds0.width >= bounds1.left &&
                bounds0.top <= bounds1.height &&
                bounds0.height >= bounds1.top)
            {
                // std::cout << "PTP bounds overlap" << std::endl;

                float inf = std::numeric_limits<float>::infinity();
                sf::Vector2f least;
                least.x  = inf;
                least.y = inf;
                float minGap = inf;
                uint32_t normalsLen = poly0->getPointCount() + poly1->getPointCount();
                sf::Vector2f *unitNormals = new sf::Vector2f[normalsLen];

                for (uint32_t i = 0; i < poly0->getPointCount(); ++i)
                {
                    unitNormals[i] = calculateUnitNormal(*poly0, i, globalTrans0);
                }

                for (uint32_t i = 0; i < poly1->getPointCount(); ++i)
                {
                    unitNormals[i + poly0->getPointCount()] = calculateUnitNormal(*poly1, i, globalTrans1);
                }

                for (uint32_t i = 0; i < normalsLen; ++i)
                {
                    sf::Vector2f unitNormal = unitNormals[i];

                    float minPoint0 = inf;
                    float maxPoint0 = -inf;
                    for (uint32_t k = 0; k < poly0->getPointCount(); ++k)
                    {
                        float point = projectPoint(*poly0, unitNormal, k, globalTrans0);
                        if (point < minPoint0)
                        {
                            minPoint0 = point;
                        }
                        if (point > maxPoint0)
                        {
                            maxPoint0 = point;
                        }
                    }

                    float minPoint1 = inf;
                    float maxPoint1 = -inf;
                    for (uint32_t k = 0; k < poly1->getPointCount(); ++k)
                    {
                        float point = projectPoint(*poly1, unitNormal, k, globalTrans1);
                        if (point < minPoint1)
                        {
                            minPoint1 = point;
                        }
                        if (point > maxPoint1)
                        {
                            maxPoint1 = point;
                        }
                    }

                    float gap = 0.0f;
                    if ((minPoint1 >= minPoint0 && minPoint1 <= maxPoint0) ||//min2 is inside 1
                        (maxPoint0 >= minPoint1 && maxPoint0 <= maxPoint1))  //max1 is inside 2
                    {
                        gap = minPoint1 - maxPoint0;
                    }
                    else if ((maxPoint1 >= minPoint0 && maxPoint1 <= maxPoint0) ||//max2 is inside 1
                             (minPoint0 >= minPoint1 && minPoint0 <= maxPoint1))  //min1 is inside 2
                    {
                        gap = maxPoint1 - minPoint0;
                    }
                    else
                    {
                        delete [] unitNormals;

                        return false;
                    }

                    if (fabs(gap) < fabs(minGap))
                    {
                        minGap = gap;
                        least.x = unitNormal.x * minGap;
                        least.y = unitNormal.y * minGap;
                    }
                }

                collisionVector.x = least.x;
                collisionVector.y = least.y;

                delete [] unitNormals;

                return true;
            }
        }

        return false;
    }

    bool CollisionUtility::collides_ctp(const sf::CircleShape *circle,
                                        const sf::Shape *poly,
                                        const sf::Transform &globalTrans0,
                                        const sf::Transform &globalTrans1,
                                        sf::Vector2f &collisionVector) const
    {
        if (this->circleIsElipse(*circle, globalTrans0))
        {
            //Circle is elipse, therefore we have to approximate it as a polygon
            const sf::ConvexShape shape = this->approximateCircle(*circle, globalTrans0);
            return this->collides_ptp(&shape,
                                      poly,
                                      globalTrans0,
                                      globalTrans1,
                                      collisionVector);
        }

        // std::cout << "Begin ctp" << std::endl;
        if (circle != NULL && poly != NULL)
        {
            sf::FloatRect bounds0 = circle->getGlobalBounds();
            bounds0 = globalTrans0.transformRect(bounds0);
            bounds0.width += bounds0.left;
            bounds0.height += bounds0.top;

            sf::FloatRect bounds1 = poly->getGlobalBounds();
            bounds1 = globalTrans1.transformRect(bounds1);
            bounds1.width += bounds0.left;
            bounds1.height += bounds1.top;

            if (bounds0.left <= bounds1.width &&
                bounds0.width >= bounds1.left &&
                bounds0.top <= bounds1.height &&
                bounds0.height >= bounds1.top)
            {
                // std::cout << "CTP bounds overlap" << std::endl;

                float inf = std::numeric_limits<float>::infinity();
                float minDist = inf;
                sf::Vector2f circleNormal;
                sf::Vector2f least(inf, inf);
                float minGap = inf;
                sf::Vector2f edgePoint;
                edgePoint.x = 2.0f * circle->getRadius();
                edgePoint.y = circle->getRadius();
                edgePoint = globalTrans0.transformPoint(circle->getTransform().transformPoint(edgePoint));
                sf::Vector2f center = globalTrans0.transformPoint(circle->getTransform().transformPoint(sf::Vector2f(circle->getRadius(), circle->getRadius())));
                float xDiff = (edgePoint.x - center.x);
                float yDiff = (edgePoint.y - center.y);
                float distance = xDiff * xDiff + yDiff * yDiff;
                float globalR = sqrt(distance);
                std::size_t normalsLen = poly->getPointCount() + 1;
                sf::Vector2f *unitNormals = new sf::Vector2f[normalsLen];

                for (uint32_t i = 0; i < poly->getPointCount(); ++i)
                {
                    sf::Vector2f currentVertex = globalTrans1.transformPoint(poly->getTransform().transformPoint(poly->getPoint(i)));
                    float xDiff = (currentVertex.x - center.x);
                    float yDiff = (currentVertex.y - center.y);
                    float distance = xDiff * xDiff + yDiff * yDiff;
                    if (distance < minDist)
                    {
                        minDist = distance;
                        circleNormal.x = xDiff;
                        circleNormal.y = yDiff;
                        float mag = sqrt(distance);
                        circleNormal.x /= mag;
                        circleNormal.y /= mag;
                    }

                    unitNormals[i] = calculateUnitNormal(*poly, i, globalTrans1);
                }
                unitNormals[normalsLen - 1] = circleNormal;

                for (uint32_t i = 0; i < normalsLen; ++i)
                {
                    sf::Vector2f unitNormal = unitNormals[i];

                    float dot = center.x * unitNormal.x + center.y * unitNormal.y;
                    float minPoint0 = dot - globalR;
                    float maxPoint0 = dot + globalR;
                    if (minPoint0 > maxPoint0)
                    {
                        float temp = minPoint0;
                        minPoint0 = maxPoint0;
                        maxPoint0 = temp;
                    }

                    float minPoint1 = inf;
                    float maxPoint1 = -inf;
                    for (uint32_t k = 0; k < poly->getPointCount(); ++k)
                    {
                        float point = projectPoint(*poly, unitNormal, k, globalTrans1);
                        if (point < minPoint1)
                        {
                            minPoint1 = point;
                        }
                        if (point > maxPoint1)
                        {
                            maxPoint1 = point;
                        }
                    }

                    float gap = 0.0f;
                    if ((minPoint1 >= minPoint0 && minPoint1 <= maxPoint0) ||//min2 is inside 1
                        (maxPoint0 >= minPoint1 && maxPoint0 <= maxPoint1))  //max1 is inside 2
                    {
                        gap = minPoint1 - maxPoint0;
                    }
                    else if ((maxPoint1 >= minPoint0 && maxPoint1 <= maxPoint0) ||//max2 is inside 1
                             (minPoint0 >= minPoint1 && minPoint0 <= maxPoint1))  //min1 is inside 2
                    {
                        gap = maxPoint1 - minPoint0;
                    }
                    else
                    {
                        delete [] unitNormals;

                        return false;
                    }

                    if (fabs(gap) < fabs(minGap))
                    {
                        minGap = gap;
                        least.x = unitNormal.x * minGap;
                        least.y = unitNormal.y * minGap;
                    }
                }

                collisionVector.x = least.x;
                collisionVector.y = least.y;

                delete [] unitNormals;

                return true;
            }
        }

        return false;
    }

    bool CollisionUtility::collides_ctc(const sf::CircleShape *circle0,
                                        const sf::CircleShape *circle1,
                                        const sf::Transform &globalTrans0,
                                        const sf::Transform &globalTrans1,
                                        sf::Vector2f &collisionVector) const
    {
        if (this->circleIsElipse(*circle0, globalTrans0) &&
            this->circleIsElipse(*circle1, globalTrans1))
        {
            //Both Circles are ellipses
            const sf::ConvexShape shape0 = this->approximateCircle(*circle0, globalTrans0);
            const sf::ConvexShape shape1 = this->approximateCircle(*circle1, globalTrans1);
            return this->collides_ptp(&shape0,
                                      &shape1,
                                      globalTrans0,
                                      globalTrans1,
                                      collisionVector);
        }
        else if (!this->circleIsElipse(*circle0, globalTrans0) &&
                  this->circleIsElipse(*circle1, globalTrans1))
        {
            //The second circle is an ellipse
            const sf::ConvexShape shape1 = this->approximateCircle(*circle1, globalTrans1);
            return this->collides_ctp(circle0,
                                      &shape1,
                                      globalTrans0,
                                      globalTrans1,
                                      collisionVector);
        }
        else if ( this->circleIsElipse(*circle0, globalTrans0) &&
                 !this->circleIsElipse(*circle1, globalTrans1))
        {
            //The first circle is an ellipse
            const sf::ConvexShape shape0 = this->approximateCircle(*circle0, globalTrans0);
            bool r = this->collides_ctp(circle1,
                                        &shape0,
                                        globalTrans1,
                                        globalTrans0,
                                        collisionVector);
            collisionVector.x *= -1.0f;
            collisionVector.y *= -1.0f;

            return r;
        }

        // std::cout << "Begin ctc" << std::endl;
        if (circle0 != NULL && circle1 != NULL)
        {
            sf::FloatRect bounds0 = circle0->getGlobalBounds();
            bounds0 = globalTrans0.transformRect(bounds0);
            bounds0.width += bounds0.left;
            bounds0.height += bounds0.top;

            sf::FloatRect bounds1 = circle1->getGlobalBounds();
            bounds1 = globalTrans1.transformRect(bounds1);
            bounds1.width += bounds0.left;
            bounds1.height += bounds1.top;

            if (bounds0.left <= bounds1.width &&
                bounds0.width >= bounds1.left &&
                bounds0.top <= bounds1.height &&
                bounds0.height >= bounds1.top)
            {
                // std::cout << "CTC bounds overlap" << std::endl;

                sf::Vector2f edgePoint;
                edgePoint.x = 2.0f * circle0->getRadius();
                edgePoint.y = circle0->getRadius();
                edgePoint = globalTrans0.transformPoint(circle0->getTransform().transformPoint(edgePoint));
                sf::Vector2f center0 = globalTrans0.transformPoint(circle0->getTransform().transformPoint(sf::Vector2f(circle0->getRadius(), circle0->getRadius())));
                float xDiff = (edgePoint.x - center0.x);
                float yDiff = (edgePoint.y - center0.y);
                float distance = xDiff * xDiff + yDiff * yDiff;
                float globalR0 = sqrt(distance);

                edgePoint.x = 2.0f * circle1->getRadius();
                edgePoint.y = circle1->getRadius();
                edgePoint = globalTrans1.transformPoint(circle1->getTransform().transformPoint(edgePoint));
                sf::Vector2f center1 = globalTrans1.transformPoint(circle1->getTransform().transformPoint(sf::Vector2f(circle1->getRadius(), circle1->getRadius())));
                xDiff = (edgePoint.x - center1.x);
                yDiff = (edgePoint.y - center1.y);
                distance = xDiff * xDiff + yDiff * yDiff;
                float globalR1 = sqrt(distance);

                float rSum = globalR0 + globalR1;
                xDiff = (center1.x - center0.x);
                yDiff = (center1.y - center0.y);
                distance = xDiff * xDiff + yDiff * yDiff;
                if (distance <= (rSum * rSum))
                {
                    //Get both vectors
                    sf::Vector2f centerVect0(xDiff, yDiff);
                    sf::Vector2f centerVect1(center0.x - center1.x, center0.y - center1.y);

                    //calculate Magnitudes
                    float centerVectMag0 = sqrt(centerVect0.x * centerVect0.x + centerVect0.y * centerVect0.y);
                    float centerVectMag1 = sqrt(centerVect1.x * centerVect1.x + centerVect1.y * centerVect1.y);

                    //Locate Points on circles
                    sf::Vector2f circlePoint0((centerVect0.x / centerVectMag0 * globalR0) + center0.x,
                                              (centerVect0.y / centerVectMag0 * globalR0) + center0.y);
                    sf::Vector2f circlePoint1((centerVect1.x / centerVectMag1 * globalR1) + center1.x,
                                              (centerVect1.y / centerVectMag1 * globalR1) + center1.y);
                    collisionVector = (circlePoint1 - circlePoint0);

                    return true;
                }
            }
        }

        return false;
    }

    bool CollisionUtility::collides(const sf::Transformable &t0,
                                    const sf::Transformable &t1,
                                    const sf::Transform &globalTrans0,
                                    const sf::Transform &globalTrans1,
                                    sf::Vector2f &collisionVector) const
    {
        bool isCollide = false;

        const sf::CircleShape* circle0 = dynamic_cast<const sf::CircleShape *>(&t0);
        const sf::CircleShape* circle1 = dynamic_cast<const sf::CircleShape *>(&t1);

        //Circle to Circle
        if (circle0 != NULL && circle1 != NULL)
        {
            // std::cout << "Circle: " << circle0 << " to Circle: " << circle1 << " check" << std::endl;
            if (this->collides_ctc(dynamic_cast<const sf::CircleShape *>(&t0),
                                   dynamic_cast<const sf::CircleShape *>(&t1),
                                   globalTrans0,
                                   globalTrans1,
                                   collisionVector))
            {
                isCollide = true;
            }
        }
        //Circle to polygon
        else if (circle0 != NULL && circle1 == NULL)
        {
            const sf::Shape* poly = this->shapeOfTransformable(t1);
            // std::cout << "Circle: " << circle0 << " to Polygon " << poly << " check" << std::endl;
            if (this->collides_ctp(circle0,
                                   poly,
                                   globalTrans0,
                                   globalTrans1,
                                   collisionVector))
            {
                isCollide = true;
            }
            if (poly)
            {
                delete poly;
            }
        }
        //polygon to circle
        else if (circle0 == NULL && circle1 != NULL)
        {
            const sf::Shape* poly = this->shapeOfTransformable(t0);
            // std::cout << "Polygon: " << poly << " to Circle: " << circle1 << " check" << std::endl;
            if (this->collides_ctp(circle1,
                                   poly,
                                   globalTrans1,
                                   globalTrans0,
                                   collisionVector))
            {
                collisionVector.x *= -1.0f;
                collisionVector.y *= -1.0f;
                isCollide = true;
            }
            if (poly)
            {
                delete poly;
            }
        }
        //polygon to polygon
        else
        {
            const sf::Shape* poly0 = this->shapeOfTransformable(t0);
            const sf::Shape* poly1 = this->shapeOfTransformable(t1);
            // std::cout << "Polygon: " << poly0 << " to Polygon: " << poly1 << " check" << std::endl;
            if (this->collides_ptp(poly0,
                                   poly1,
                                   globalTrans0,
                                   globalTrans1,
                                   collisionVector))
            {
                isCollide = true;
            }
            if (poly0)
            {
                delete poly0;
            }
            if (poly1)
            {
                delete poly1;
            }
        }

        // std::cout << "isCollide: " << isCollide << std::endl;
        return isCollide;
    }
}