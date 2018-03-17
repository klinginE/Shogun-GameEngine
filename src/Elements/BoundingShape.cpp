//C++ includes
#include <stdexcept>
#include <typeinfo>
#include <limits>
#include <iostream>
#include <math.h>

//Shogun includes
#include <Shogun/Elements/BoundingShape.hpp>

namespace sg {

    std::vector<sf::Shape *>::size_type BoundingShape::getNumOfShapes() const {

        return this->shapes.size();

    }

    const sf::Shape *BoundingShape::getShape(uint32_t idx) const {

        if (idx >= this->getNumOfShapes())
            return NULL;
        return this->shapes[idx];

    }

    std::vector<sf::Shape *>::size_type BoundingShape::addShape(sf::Shape &newShape) {

        this->shapes.push_back(&newShape);
        return (this->getNumOfShapes() - 1);

    }

    sf::Shape *BoundingShape::removeShape(uint32_t idx) {

        if (idx >= this->getNumOfShapes())
            return NULL;

        sf::Shape *s = this->shapes[idx];
        this->shapes.erase(this->shapes.begin() + idx);

        return s;

    }

    void BoundingShape::setOriginShape(uint32_t idx, const sf::Vector2f &origin) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->setOrigin(origin);

    }

    void BoundingShape::setPositionShape(uint32_t idx, const sf::Vector2f &newPos) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->setPosition(newPos);

    }

    void BoundingShape::moveShape(uint32_t idx, const sf::Vector2f &offset) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->move(offset);

    }

    void BoundingShape::setRotationShape(uint32_t idx, float angle) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->setRotation(angle);

    }

    void BoundingShape::rotateShape(uint32_t idx, float angle) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->rotate(angle);

    }

    void BoundingShape::setScaleShape(uint32_t idx, const sf::Vector2f &factor) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->setScale(factor);

    }

    void BoundingShape::scaleShape(uint32_t idx, const sf::Vector2f &factor) {

        if (idx >= this->getNumOfShapes())
            return;
        this->shapes[idx]->scale(factor);

    }

    sf::FloatRect BoundingShape::getBounds(bool useLocal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (const sf::Shape *s : this->shapes) {

            sf::FloatRect br;
            if (useLocal)
                br = s->getLocalBounds();
            else
                br = this->getTransform().transformRect(s->getGlobalBounds());

            if (br.left < bounds.left)
                bounds.left = br.left;
            if (br.top < bounds.top)
                bounds.top = br.top;
            if ((br.left + br.width) > bounds.width)
                bounds.width = (br.left + br.width);
            if ((br.top + br.height) > bounds.height)
                bounds.height = (br.top + br.height);

        }

        bounds.width -= bounds.left;
        bounds.height -= bounds.top;

        return bounds;

    }

    sf::FloatRect BoundingShape::getLocalBounds() const {

        return this->getBounds(true);

    }

    sf::FloatRect BoundingShape::getGlobalBounds() const {

        return this->getBounds(false);

    }

    const sf::ConvexShape BoundingShape::approximateCircle(const sf::CircleShape &circle,
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

    sf::Vector2f BoundingShape::calculateUnitNormal(const sf::Shape &poly,
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

    float BoundingShape::projectPoint(const sf::Shape &poly,
                                      const sf::Vector2f &unitNormal,
                                      uint32_t k,
                                      const sf::Transform &globalTrans) const
    {
        sf::Vector2f vertex = globalTrans.transformPoint(poly.getTransform().transformPoint(poly.getPoint(k)));
        float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;

        return point;
    }

    bool BoundingShape::collides_ptp(const sf::Shape &poly0,
                                     const sf::Shape &poly1,
                                     sf::Vector2f &collisionVector,
                                     const sf::Transform &globalTrans0,
                                     const sf::Transform &globalTrans1) const
    {
        if (dynamic_cast<const sf::CircleShape *>(&poly0))
        {
            std::cerr << "collides_ptp(): poly0 is circle shape not polygon." << std::endl;
            throw std::bad_typeid();
        }
        if (dynamic_cast<const sf::CircleShape *>(&poly1))
        {
            std::cerr << "collides_ptp(): poly1 is circle shape not polygon." << std::endl;
            throw std::bad_typeid();
        }

        float inf = std::numeric_limits<float>::infinity();
        sf::Vector2f least;
        least.x  = inf;
        least.y = inf;
        float minGap = inf;
        uint32_t normalsLen = poly0.getPointCount() + poly1.getPointCount();
        sf::Vector2f *unitNormals = new sf::Vector2f[normalsLen];

        for (uint32_t i = 0; i < poly0.getPointCount(); ++i)
        {
            unitNormals[i] = calculateUnitNormal(poly0, i, globalTrans0);
        }

        for (uint32_t i = 0; i < poly1.getPointCount(); ++i)
        {
            unitNormals[i + poly0.getPointCount()] = calculateUnitNormal(poly1, i, globalTrans1);
        }

        for (uint32_t i = 0; i < normalsLen; ++i)
        {
            sf::Vector2f unitNormal = unitNormals[i];
 
            float minPoint0 = inf;
            float maxPoint0 = -inf;
            for (uint32_t k = 0; k < poly0.getPointCount(); ++k)
            {
                float point = projectPoint(poly0, unitNormal, k, globalTrans0);
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
            for (uint32_t k = 0; k < poly1.getPointCount(); ++k)
            {
                float point = projectPoint(poly1, unitNormal, k, globalTrans1);
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

    bool BoundingShape::collides_ctp(const sf::Shape &poly0,
                                     const sf::Shape &poly1,
                                     sf::Vector2f &collisionVector,
                                     const sf::Transform &globalTrans0,
                                     const sf::Transform &globalTrans1) const
    {
        if (!(dynamic_cast<const sf::CircleShape *>(&poly0)))
        {
            std::cerr << "collisdes_ctp(): poly0 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();
        }

        if (dynamic_cast<const sf::CircleShape *>(&poly1))
        {
            std::cerr << "collisdes_ctp(): poly1 is a circle not a polygon." << std::endl;
            throw std::bad_typeid();
        }

        const sf::CircleShape &circle = dynamic_cast<const sf::CircleShape &>(poly0);
        sf::Vector2f p0 = globalTrans0.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(2.0f * circle.getRadius(), circle.getRadius())));
        sf::Vector2f p1 = globalTrans0.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(circle.getRadius(), 2.0f * circle.getRadius())));
        sf::Vector2f center = globalTrans0.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(circle.getRadius(), circle.getRadius())));
        p0 -= center;
        p1 -= center;
        float transRadius0 = std::round(std::sqrt(p0.x * p0.x + p0.y * p0.y));
        float transRadius1 = std::round(std::sqrt(p1.x * p1.x + p1.y * p1.y));
        if (transRadius0 <  transRadius1 || transRadius0 > transRadius1)
        {
            return this->collides_ptp(this->approximateCircle(circle, globalTrans0), poly1, collisionVector, globalTrans0, globalTrans1);
        }

        float inf = std::numeric_limits<float>::infinity();
        float minDist = inf;
        sf::Vector2f circleNormal;
        sf::Vector2f least;
        least.x = inf;
        least.y = inf;
        float minGap = inf;
        sf::Vector2f edgePoint;
        edgePoint.x = 2.0f * circle.getRadius();
        edgePoint.y = circle.getRadius();
        edgePoint = globalTrans0.transformPoint(circle.getTransform().transformPoint(edgePoint));
        float xDiff = (edgePoint.x - center.x);
        float yDiff = (edgePoint.y - center.y);
        float distance = xDiff * xDiff + yDiff * yDiff;
        float globalR = sqrt(distance);
        std::size_t normalsLen = poly1.getPointCount() + 1;
        sf::Vector2f *unitNormals = new sf::Vector2f[normalsLen];

        for (uint32_t i = 0; i < poly1.getPointCount(); ++i)
        {
            sf::Vector2f currentVertex = globalTrans1.transformPoint(poly1.getTransform().transformPoint(poly1.getPoint(i)));
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

            unitNormals[i] = calculateUnitNormal(poly1, i, globalTrans1);
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
            for (uint32_t k = 0; k < poly1.getPointCount(); ++k)
            {
                float point = projectPoint(poly1, unitNormal, k, globalTrans1);
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

    bool BoundingShape::collides_ctc(const sf::Shape &poly0,
                                     const sf::Shape &poly1,
                                     const sf::Transform &globalTrans0,
                                     const sf::Transform &globalTrans1,
                                     sf::Vector2f &collisionVector) const
    {
        if (!(dynamic_cast<const sf::CircleShape *>(&poly0)))
        {
            std::cerr << "collides_ctc(): poly0 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();
        }
        if (!(dynamic_cast<const sf::CircleShape *>(&poly1)))
        {
            std::cerr << "collides_ctc(): poly1 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();
        }

        const sf::CircleShape &circle0 = dynamic_cast<const sf::CircleShape &>(poly0);
        const sf::CircleShape &circle1 = dynamic_cast<const sf::CircleShape &>(poly1);

        sf::Vector2f p0_0 = globalTrans0.transformPoint(circle0.getTransform().transformPoint(sf::Vector2f(2.0f * circle0.getRadius(), circle0.getRadius())));
        sf::Vector2f p1_0 = globalTrans0.transformPoint(circle0.getTransform().transformPoint(sf::Vector2f(circle0.getRadius(), 2.0f * circle0.getRadius())));
        sf::Vector2f center0 = globalTrans0.transformPoint(circle0.getTransform().transformPoint(sf::Vector2f(circle0.getRadius(), circle0.getRadius())));
        p0_0 -= center0;
        p1_0 -= center0;
        float transRadius0_0 = std::round(std::sqrt(p0_0.x * p0_0.x + p0_0.y * p0_0.y));
        float transRadius1_0 = std::round(std::sqrt(p1_0.x * p1_0.x + p1_0.y * p1_0.y));

        sf::Vector2f p0_1 = globalTrans0.transformPoint(circle1.getTransform().transformPoint(sf::Vector2f(2.0f * circle1.getRadius(), circle1.getRadius())));
        sf::Vector2f p1_1 = globalTrans0.transformPoint(circle1.getTransform().transformPoint(sf::Vector2f(circle1.getRadius(), 2.0f * circle1.getRadius())));
        sf::Vector2f center1 = globalTrans0.transformPoint(circle1.getTransform().transformPoint(sf::Vector2f(circle1.getRadius(), circle1.getRadius())));
        p0_1 -= center1;
        p1_1 -= center1;
        float transRadius0_1 = std::round(std::sqrt(p0_1.x * p0_1.x + p0_1.y * p0_1.y));
        float transRadius1_1 = std::round(std::sqrt(p1_1.x * p1_1.x + p1_1.y * p1_1.y));

        if ((transRadius0_0 < transRadius1_0 || transRadius0_0 > transRadius1_0) &&
            (transRadius0_1 < transRadius1_1 || transRadius0_1 > transRadius1_1))
        {
            return this->collides_ptp(this->approximateCircle(circle0, globalTrans0),
                                      this->approximateCircle(circle1, globalTrans1),
                                      collisionVector,
                                      globalTrans0,
                                      globalTrans1);
        }
        else if (!(transRadius0_0 < transRadius1_0 || transRadius0_0 > transRadius1_0) &&
                  (transRadius0_1 < transRadius1_1 || transRadius0_1 > transRadius1_1))
        {
            return this->collides_ctp(poly0,
                                      this->approximateCircle(circle1, globalTrans1),
                                      collisionVector,
                                      globalTrans0,
                                      globalTrans0);
        }
        else if ( (transRadius0_0 < transRadius1_0 || transRadius0_0 > transRadius1_0) &&
                 !(transRadius0_1 < transRadius1_1 || transRadius0_1 > transRadius1_1))
        {
            bool r = this->collides_ctp(poly1,
                                        this->approximateCircle(circle0, globalTrans0),
                                        collisionVector,
                                        globalTrans1,
                                        globalTrans0);
            collisionVector.x *= -1.0f;
            collisionVector.y *= -1.0f;

            return r;
        }

        sf::Vector2f edgePoint;
        edgePoint.x = 2.0f * circle0.getRadius();
        edgePoint.y = circle0.getRadius();
        edgePoint = globalTrans0.transformPoint(circle0.getTransform().transformPoint(edgePoint));
        float xDiff = (edgePoint.x - center0.x);
        float yDiff = (edgePoint.y - center0.y);
        float distance = xDiff * xDiff + yDiff * yDiff;
        float globalR0 = sqrt(distance);

        edgePoint.x = 2.0f * circle1.getRadius();
        edgePoint.y = circle1.getRadius();
        edgePoint = globalTrans1.transformPoint(circle1.getTransform().transformPoint(edgePoint));
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

        return false;
    }

    bool BoundingShape::collides(const sf::Shape &s0,
                                 const sf::Shape &s1,
                                 const sf::Transform &globalTrans0,
                                 const sf::Transform &globalTrans1,
                                 sf::Vector2f &collisionVector) const
    {
        bool isCollide = false;
        //Circle to Circle
        if (dynamic_cast<const sf::CircleShape *>(&s0) &&
            dynamic_cast<const sf::CircleShape *>(&s1))
        {
            if (this->collides_ctc(s0, s1, globalTrans0, globalTrans1, collisionVector))
            {
                isCollide = true;
            }
        }
        //Circle to polygon
        else if (dynamic_cast<const sf::CircleShape *>(&s0) &&
                 !dynamic_cast<const sf::CircleShape *>(&s1))
        {
            if (this->collides_ctp(s0, s1, collisionVector, globalTrans0, globalTrans1))
            {
                isCollide = true;
            }
        }
        //polygon to circle
        else if (!dynamic_cast<const sf::CircleShape *>(&s0) &&
                 dynamic_cast<const sf::CircleShape *>(&s1))
        {
            if (this->collides_ctp(s1, s0, collisionVector, globalTrans1, globalTrans0))
            {
                collisionVector.x *= -1.0f;
                collisionVector.y *= -1.0f;
                isCollide = true;
            }
        }
        //polygon to polygon
        else
        {
            if (this->collides_ptp(s0, s1, collisionVector, globalTrans0, globalTrans1))
            {
                isCollide = true;
            }
        }

        return isCollide;
    }
}
