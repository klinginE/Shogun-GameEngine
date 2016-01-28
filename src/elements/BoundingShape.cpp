//C++ includes
#include <stdexcept>
#include <typeinfo>
#include <limits>
#include <iostream>
#include <math.h>

//SHOGUN includes
#include "BoundingShape.hpp"

namespace sg {

    BoundingShape::~BoundingShape() {

        this->shapes.clear();

    }

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

        this->shapes[idx]->setOrigin(origin);

    }

    void BoundingShape::setPositionShape(uint32_t idx, const sf::Vector2f &newPos) {

        this->shapes[idx]->setPosition(newPos);

    }

    void BoundingShape::moveShape(uint32_t idx, const sf::Vector2f &offset) {

        this->shapes[idx]->move(offset);

    }

    void BoundingShape::setRotationShape(uint32_t idx, float angle) {

        this->shapes[idx]->setRotation(angle);

    }

    void BoundingShape::rotateShape(uint32_t idx, float angle) {

        this->shapes[idx]->rotate(angle);

    }

    void BoundingShape::setScaleShape(uint32_t idx, const sf::Vector2f &factor) {

        this->shapes[idx]->setScale(factor);

    }

    void BoundingShape::scaleShape(uint32_t idx, const sf::Vector2f &factor) {

        this->shapes[idx]->scale(factor);

    }

    sf::FloatRect BoundingShape::getBounds(bool useLocal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (const auto &it : this->shapes) {

            sf::Shape *s = it;
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

    const sf::ConvexShape BoundingShape::approximateCircle(const sf::CircleShape &circle, const sf::Transform &globalTrans) const {

        sf::FloatRect gb = globalTrans.transformRect(circle.getGlobalBounds());
        uint32_t n = static_cast<uint32_t>(ceil(gb.width * gb.height / 2.0f)) + 30;
        sf::ConvexShape approxCircle(n);
        approxCircle.setPoint(0, sf::Vector2f(2.0f * circle.getRadius(), circle.getRadius()));
        float angle = 360.0f / static_cast<float>(n);
        sf::Transform rotation;
        rotation.rotate(angle, sf::Vector2f(circle.getRadius(), circle.getRadius()));
        for (uint32_t i = 0; i < (n - 1); i++)
            approxCircle.setPoint(i + 1, rotation.transformPoint(approxCircle.getPoint(i)));

        return approxCircle;

    }

    sf::Vector2f BoundingShape::calculateUnitNormal(const sf::Shape &poly, uint32_t i, const sf::Transform &globalTrans) const {

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

    float BoundingShape::projectPoint(const sf::Shape &poly, const sf::Vector2f &unitNormal, uint32_t k, const sf::Transform &globalTrans) const {

        sf::Vector2f vertex = globalTrans.transformPoint(poly.getTransform().transformPoint(poly.getPoint(k)));
        float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;

        return point;

    }

    bool BoundingShape::collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least, const sf::Transform &globalTrans1, const sf::Transform &globalTrans2) const {

        if (dynamic_cast<const sf::CircleShape *>(&poly1)) {

            std::cerr << "collides_ptp(): poly1 is circle shape not polygon." << std::endl;
            throw std::bad_typeid();

        }
        if (dynamic_cast<const sf::CircleShape *>(&poly2)) {

            std::cerr << "collides_ptp(): poly2 is circle shape not polygon." << std::endl;
            throw std::bad_typeid();

        }

        float inf = std::numeric_limits<float>::infinity();
        least.x  = inf;
        least.y = inf;
        float minGap = inf;
        uint32_t normalsLen = poly1.getPointCount() + poly2.getPointCount();
        sf::Vector2f *unitNormals = new sf::Vector2f[normalsLen];

        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < poly1.getPointCount(); i++)
            unitNormals[i] = calculateUnitNormal(poly1, i, globalTrans1);

        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < poly2.getPointCount(); i++)
            unitNormals[i + poly1.getPointCount()] = calculateUnitNormal(poly2, i, globalTrans2);

        for (uint32_t i = 0; i < normalsLen; i++) {

            sf::Vector2f unitNormal = unitNormals[i];
 
            float minPoint1 = inf;
            float maxPoint1 = -inf;
            #ifdef PARALLEL_ENABLED
            #pragma omp parallel for
            #endif
            for (uint32_t k = 0; k < poly1.getPointCount(); k++) {

                float point = projectPoint(poly1, unitNormal, k, globalTrans1);
                #ifdef PARALLEL_ENABLED
                #pragma omp flush(minPoint1)
                #endif
                if (point < minPoint1) {

                    #ifdef PARALLEL_ENABLED
                    #pragma omp critical
                    if (point < minPoint1)
                    #endif
                    minPoint1 = point;

                }
                #ifdef PARALLEL_ENABLED
                #pragma omp flush(maxPoint1)
                #endif
                if (point > maxPoint1) {

                    #ifdef PARALLEL_ENABLED
                    #pragma omp critical
                    if (point > maxPoint1)
                    #endif
                    maxPoint1 = point;

                }

            }

            float minPoint2 = inf;
            float maxPoint2 = -inf;
            #ifdef PARALLEL_ENABLED
            #pragma omp parallel for
            #endif
            for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

                float point = projectPoint(poly2, unitNormal, k, globalTrans2);
                #ifdef PARALLEL_ENABLED
                #pragma omp flush(minPoint2)
                #endif
                if (point < minPoint2) {

                    #ifdef PARALLEL_ENABLED
                    #pragma omp critical
                    if (point < minPoint2)
                    #endif
                    minPoint2 = point;

                }
                #ifdef PARALLEL_ENABLED
                #pragma omp flush(maxPoint2)
                #endif
                if (point > maxPoint2) {

                    #ifdef PARALLEL_ENABLED
                    #pragma omp critical
                    if (point > maxPoint2)
                    #endif
                    maxPoint2 = point;

                }

            }

            float gap = 0.0f;
            if ((minPoint2 >= minPoint1 && minPoint2 <= maxPoint1) ||//min2 is inside 1
                (maxPoint1 >= minPoint2 && maxPoint1 <= maxPoint2))  //max1 is inside 2
                gap = minPoint2 - maxPoint1;
            else if ((maxPoint2 >= minPoint1 && maxPoint2 <= maxPoint1) ||//max2 is inside 1
                     (minPoint1 >= minPoint2 && minPoint1 <= maxPoint2))  //min1 is inside 2
                gap = maxPoint2 - minPoint1;
            else {

                delete [] unitNormals;
                return false;

            }

            if (fabs(gap) < fabs(minGap)) {

                minGap = gap;
                least.x = unitNormal.x * minGap;
                least.y = unitNormal.y * minGap;

            }

        }

        delete [] unitNormals;
        return true;

    }

    bool BoundingShape::collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least, const sf::Transform &globalTrans1, const sf::Transform &globalTrans2) const {

        if (!(dynamic_cast<const sf::CircleShape *>(&poly1))) {

            std::cerr << "collisdes_ctp(): poly1 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();

        }
        if (dynamic_cast<const sf::CircleShape *>(&poly2)) {

            std::cerr << "collisdes_ctp(): poly2 is a circle not a polygon." << std::endl;
            throw std::bad_typeid();

        }

        const sf::CircleShape &circle = dynamic_cast<const sf::CircleShape &>(poly1);
        sf::FloatRect circleBounds = globalTrans1.transformRect(circle.getGlobalBounds());
        if (circleBounds.width < circleBounds.height || circleBounds.width > circleBounds.height)
            return this->collides_ptp(this->approximateCircle(circle, globalTrans1), poly2, least, globalTrans1, globalTrans2);

        sf::Vector2f center = globalTrans1.transformPoint(circle.getTransform().transformPoint(sf::Vector2f(circle.getRadius(), circle.getRadius())));
        float inf = std::numeric_limits<float>::infinity();
        float minDist = inf;
        sf::Vector2f circleNormal;

        least.x = inf;
        least.y = inf;
        float minGap = inf;
        sf::Vector2f edgePoint;
        edgePoint.x = 2.0f * circle.getRadius();
        edgePoint.y = circle.getRadius();
        edgePoint = globalTrans1.transformPoint(circle.getTransform().transformPoint(edgePoint));
        float xDiff = (edgePoint.x - center.x);
        float yDiff = (edgePoint.y - center.y);
        float distance = xDiff * xDiff + yDiff * yDiff;
        float globalR = sqrt(distance);
        std::size_t normalsLen = poly2.getPointCount() + 1;
        sf::Vector2f *unitNormals = new sf::Vector2f[normalsLen];

        #ifdef PARALLEL_ENABLED
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < poly2.getPointCount(); i++) {

            sf::Vector2f currentVertex = globalTrans2.transformPoint(poly2.getTransform().transformPoint(poly2.getPoint(i)));
            xDiff = (currentVertex.x - center.x);
            yDiff = (currentVertex.y - center.y);
            distance = xDiff * xDiff + yDiff * yDiff;
            #ifdef PARALLEL_ENABLED
            #pragma omp critical
            {
            #endif
            if (distance < minDist) {

                minDist = distance;
                circleNormal.x = xDiff;
                circleNormal.y = yDiff;
                float mag = sqrt(distance);
                circleNormal.x /= mag;
                circleNormal.y /= mag;

            }
            #ifdef PARALLEL_ENABLED
            }
            #endif

            unitNormals[i] = calculateUnitNormal(poly2, i, globalTrans2);

        }
        unitNormals[normalsLen - 1] = circleNormal;

        for (uint32_t i = 0; i < normalsLen; i++) {

            sf::Vector2f unitNormal = unitNormals[i];

            float dot = center.x * unitNormal.x + center.y * unitNormal.y;
            float minPoint1 = dot - globalR;
            float maxPoint1 = dot + globalR;
            if (minPoint1 > maxPoint1) {

                float temp = minPoint1;
                minPoint1 = maxPoint1;
                maxPoint1 = temp;

            }

            float minPoint2 = inf;
            float maxPoint2 = -inf;
            #ifdef PARALLEL_ENABLED
            #pragma omp parallel for
            #endif
            for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

                float point = projectPoint(poly2, unitNormal, k, globalTrans2);
                #ifdef PARALLEL_ENABLED
                #pragma omp flush(minPoint2)
                #endif
                if (point < minPoint2) {

                    #ifdef PARALLEL_ENABLED
                    #pragma omp critical
                    if (point < minPoint2)
                    #endif
                    minPoint2 = point;

                }
                #ifdef PARALLEL_ENABLED
                #pragma omp flush(maxPoint2)
                #endif
                if (point > maxPoint2) {

                    #ifdef PARALLEL_ENABLED
                    #pragma omp critical
                    if (point > maxPoint2)
                    #endif
                    maxPoint2 = point;

                }

            }

            float gap = 0.0f;
            if ((minPoint2 >= minPoint1 && minPoint2 <= maxPoint1) ||//min2 is inside 1
                (maxPoint1 >= minPoint2 && maxPoint1 <= maxPoint2))  //max1 is inside 2
                gap = minPoint2 - maxPoint1;
            else if ((maxPoint2 >= minPoint1 && maxPoint2 <= maxPoint1) ||//max2 is inside 1
                     (minPoint1 >= minPoint2 && minPoint1 <= maxPoint2))  //min1 is inside 2
                gap = maxPoint2 - minPoint1;
            else {

                delete [] unitNormals;
                return false;

            }

            if (fabs(gap) < fabs(minGap)) {

                minGap = gap;
                least.x = unitNormal.x * minGap;
                least.y = unitNormal.y * minGap;

            }

        }

        delete [] unitNormals;
        return true;

    }

    bool BoundingShape::collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least, const sf::Transform &globalTrans1, const sf::Transform &globalTrans2) const {

        if (!(dynamic_cast<const sf::CircleShape *>(&poly1))) {

            std::cerr << "collides_ctc(): poly1 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();

        }
        if (!(dynamic_cast<const sf::CircleShape *>(&poly2))) {

            std::cerr << "collides_ctc(): poly2 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();

        }

        const sf::CircleShape &circle1 = dynamic_cast<const sf::CircleShape &>(poly1);
        const sf::CircleShape &circle2 = dynamic_cast<const sf::CircleShape &>(poly2);
        sf::FloatRect circleBounds1 = globalTrans1.transformRect(circle1.getGlobalBounds());
        sf::FloatRect circleBounds2 = globalTrans2.transformRect(circle2.getGlobalBounds());
        if ((circleBounds1.width < circleBounds1.height || circleBounds1.width > circleBounds1.height) &&
            (circleBounds2.width < circleBounds2.height || circleBounds2.width > circleBounds2.height))
            return this->collides_ptp(this->approximateCircle(circle1, globalTrans1), this->approximateCircle(circle2, globalTrans2), least, globalTrans1, globalTrans2);

        else if (!(circleBounds1.width < circleBounds1.height || circleBounds1.width > circleBounds1.height) &&
                 (circleBounds2.width < circleBounds2.height || circleBounds2.width > circleBounds2.height))
            return this->collides_ctp(poly1, this->approximateCircle(circle2, globalTrans2), least, globalTrans1, globalTrans2);
        else if ((circleBounds1.width < circleBounds1.height || circleBounds1.width > circleBounds1.height) &&
                 !(circleBounds2.width < circleBounds2.height || circleBounds2.width > circleBounds2.height)) {

            bool r = this->collides_ctp(poly2, this->approximateCircle(circle1, globalTrans1), least, globalTrans2, globalTrans1);
            least.x = -least.x;
            least.y = -least.y;

            return r;

        }

        sf::Vector2f center1 = globalTrans1.transformPoint(circle1.getTransform().transformPoint(sf::Vector2f(circle1.getRadius(), circle1.getRadius())));
        sf::Vector2f center2 = globalTrans2.transformPoint(circle2.getTransform().transformPoint(sf::Vector2f(circle2.getRadius(), circle2.getRadius())));

        sf::Vector2f edgePoint;
        edgePoint.x = 2.0f * circle1.getRadius();
        edgePoint.y = circle1.getRadius();
        edgePoint = globalTrans1.transformPoint(circle1.getTransform().transformPoint(edgePoint));
        float xDiff = (edgePoint.x - center1.x);
        float yDiff = (edgePoint.y - center1.y);
        float distance = xDiff * xDiff + yDiff * yDiff;
        float globalR1 = sqrt(distance);

        edgePoint.x = 2.0f * circle2.getRadius();
        edgePoint.y = circle2.getRadius();
        edgePoint = globalTrans2.transformPoint(circle2.getTransform().transformPoint(edgePoint));
        xDiff = (edgePoint.x - center2.x);
        yDiff = (edgePoint.y - center2.y);
        distance = xDiff * xDiff + yDiff * yDiff;
        float globalR2 = sqrt(distance);
        
        float rSum = globalR1 + globalR2;
        xDiff = (center2.x - center1.x);
        yDiff = (center2.y - center1.y);
        distance = xDiff * xDiff + yDiff * yDiff;
        if (distance <= (rSum * rSum)) {

            //Get both vectors
            sf::Vector2f centerVect1(xDiff, yDiff);
            sf::Vector2f centerVect2(center1.x - center2.x, center1.y - center2.y);

            //calculate Magnitudes
            float centerVectMag1 = sqrt(centerVect1.x * centerVect1.x + centerVect1.y * centerVect1.y);
            float centerVectMag2 = sqrt(centerVect2.x * centerVect2.x + centerVect2.y * centerVect2.y);

            //Locate Points on circles
            sf::Vector2f circlePoint1((centerVect1.x / centerVectMag1 * globalR1) + center1.x,
                                      (centerVect1.y / centerVectMag1 * globalR1) + center1.y);
            sf::Vector2f circlePoint2((centerVect2.x / centerVectMag2 * globalR2) + center2.x,
                                      (centerVect2.y / centerVectMag2 * globalR2) + center2.y);

            least.x = circlePoint2.x - circlePoint1.x;
            least.y = circlePoint2.y - circlePoint1.y;

            return true;

        }

        return false;

    }

    bool BoundingShape::collides(const BoundingShape &bs, sf::Vector2f &least, const sf::Transform &globalTrans1, const sf::Transform &globalTrans2) const {

        least.x = 0.0f;
        least.y = 0.0f;
        bool isCollide = false;
        sf::Transform combinedGlobalTrans1 = sf::Transform::Identity;
	combinedGlobalTrans1 = combinedGlobalTrans1.combine(globalTrans1);
        combinedGlobalTrans1 = combinedGlobalTrans1.combine(this->getTransform());
        sf::Transform combinedGlobalTrans2 = sf::Transform::Identity;
        combinedGlobalTrans2 = combinedGlobalTrans2.combine(globalTrans2);
        combinedGlobalTrans2 = combinedGlobalTrans2.combine(bs.getTransform());
        for (const auto &it : this->shapes)
            for (uint32_t i = 0; i < bs.getNumOfShapes(); i++) {

                sf::Shape *s0 = it;
                const sf::Shape *s1 = bs.getShape(i);
                //Circle to Circle
                sf::Vector2f v(0.0f, 0.0f);
                if ((dynamic_cast<const sf::CircleShape *>(s0)) &&
                    (dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctc(*s0, *s1, v, combinedGlobalTrans1, combinedGlobalTrans2)) {

                        isCollide = true;
                        if (fabs(v.x) > fabs(least.x))
                            least.x = v.x;
                        if (fabs(v.y) > fabs(least.y))
                            least.y = v.y;

                    }
                }
                //Circle to polygon
                else if ((dynamic_cast<const sf::CircleShape *>(s0)) &&
                         !(dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctp(*s0, *s1, v, combinedGlobalTrans1, combinedGlobalTrans2)) {

                        isCollide = true;
                        if (fabs(v.x) > fabs(least.x))
                            least.x = v.x;
                        if (fabs(v.y) > fabs(least.y))
                            least.y = v.y;

                    }
                }
                //polygon to circle
                else if (!(dynamic_cast<const sf::CircleShape *>(s0)) &&
                         (dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctp(*s1, *s0, v, combinedGlobalTrans2, combinedGlobalTrans1)) {

                        v.x = -v.x;
                        v.y = -v.y;
                        isCollide = true;
                        if (fabs(v.x) > fabs(least.x))
                            least.x = v.x;
                        if (fabs(v.y) > fabs(least.y))
                            least.y = v.y;

                    }
                }
                //polygon to polygon
                else {
                    if (this->collides_ptp(*s0, *s1, v, combinedGlobalTrans1, combinedGlobalTrans2)) {

                        isCollide = true;
                        if (fabs(v.x) > fabs(least.x))
                            least.x = v.x;
                        if (fabs(v.y) > fabs(least.y))
                            least.y = v.y;

                    }
                }

            }

        return isCollide;

    }

}
