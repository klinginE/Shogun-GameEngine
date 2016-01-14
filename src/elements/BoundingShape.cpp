//C++ includes
#include <stdexcept>
#include <typeinfo>
#include <limits>
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

    const sf::Shape *BoundingShape::removeShape(uint32_t idx) {

        if (idx >= this->getNumOfShapes())
            return NULL;

        sf::Shape *s = this->shapes[idx];
        this->shapes.erase(this->shapes.begin() + idx);

        return s;

    }

    void BoundingShape::setOrigin(float x, float y) {

        this->setOrigin(sf::Vector2f(x, y));

    }

    void BoundingShape::setOrigin(const sf::Vector2f &origin) {

        sf::Transformable::setOrigin(origin);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->setOrigin(origin);

    }

    void BoundingShape::setPosition(float x, float y) {

        this->setPosition(sf::Vector2f(x, y));

    }

    void BoundingShape::setPosition(const sf::Vector2f &newPos) {

        sf::Transformable::setPosition(newPos);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->setPosition(newPos);

    }

    void BoundingShape::move(float offsetX, float offsetY) {

        this->move(sf::Vector2f(offsetX, offsetY));

    }

    void BoundingShape::move(const sf::Vector2f &offset) {

        sf::Transformable::move(offset);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->move(offset);

    }

    void BoundingShape::setRotation(float angle) {

        sf::Transformable::setRotation(angle);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->setRotation(angle);

    }

    void BoundingShape::rotate(float angle) {

        sf::Transformable::rotate(angle);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->rotate(angle);

    }

    void BoundingShape::setScale(float factorX, float factorY) {

        this->setScale(sf::Vector2f(factorX, factorY));

    }

    void BoundingShape::setScale(const sf::Vector2f &factor) {

        sf::Transformable::setScale(factor);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->setScale(factor);

    }

    void BoundingShape::scale(float factorX, float factorY) {

        this->scale(sf::Vector2f(factorX, factorY));

    }

    void BoundingShape::scale(const sf::Vector2f &factor) {

        sf::Transformable::scale(factor);
        for (std::vector<sf::Shape *>::iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            (*it)->scale(factor);

    }

    sf::FloatRect BoundingShape::getShapeBounds(bool useLocal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<sf::Shape *>::const_iterator it = this->shapes.begin(); it != this->shapes.end(); ++it) {

            sf::Shape *s = (*it);
            sf::FloatRect br(0.0f, 0.0f, 0.0f, 0.0f);
            if (useLocal)
                br = s->getLocalBounds();
            else
                br = s->getGlobalBounds();

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

    sf::FloatRect BoundingShape::getLocalShapeBounds() const {

        return this->getShapeBounds(true);

    }

    sf::FloatRect BoundingShape::getGlobalShapeBounds() const {

        return this->getShapeBounds(false);

    }

    const sf::ConvexShape BoundingShape::approximateCircle(const sf::CircleShape &circle, const sf::Transformable &globalTrans) const {

        sf::FloatRect gb = globalTrans.getTransform().transformRect(circle.getGlobalBounds());
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

    sf::Vector2f BoundingShape::calculateUnitNormal(const sf::Shape &poly, uint32_t i, const sf::Transformable &globalTrans) const {

        uint32_t j = (i + 1) % poly.getPointCount();
        sf::Vector2f currentVertex = globalTrans.getTransform().transformPoint(poly.getTransform().transformPoint(poly.getPoint(i)));
        sf::Vector2f adjacentVertex = globalTrans.getTransform().transformPoint(poly.getTransform().transformPoint(poly.getPoint(j)));
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

    float BoundingShape::projectPoint(const sf::Shape &poly, const sf::Vector2f &unitNormal, uint32_t k, const sf::Transformable &globalTrans) const {

        sf::Vector2f vertex = globalTrans.getTransform().transformPoint(poly.getTransform().transformPoint(poly.getPoint(k)));
        float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;

        return point;

    }

    bool BoundingShape::collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least, const sf::Transformable &globalTrans1, const sf::Transformable &globalTrans2) const {

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
        std::vector<sf::Vector2f> unitNormals(normalsLen);

        for (uint32_t i = 0; i < poly1.getPointCount(); i++)
            unitNormals.push_back(calculateUnitNormal(poly1, i, globalTrans1));

        for (uint32_t i = 0; i < poly2.getPointCount(); i++)
            unitNormals.push_back(calculateUnitNormal(poly2, i, globalTrans2));

        for (uint32_t i = 0; i < normalsLen; i++) {

            sf::Vector2f unitNormal = unitNormals[i];
 
            float minPoint1 = inf;
            float maxPoint1 = -inf;
            for (uint32_t k = 0; k < poly1.getPointCount(); k++) {

                float point = projectPoint(poly1, unitNormal, k, globalTrans1);
                if (point < minPoint1)
                    minPoint1 = point;
                if (point > maxPoint1)
                    maxPoint1 = point;

            }

            float minPoint2 = inf;
            float maxPoint2 = -inf;
            for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

                float point = projectPoint(poly2, unitNormal, k, globalTrans2);
                if (point < minPoint2)
                    minPoint2 = point;
                if (point > maxPoint2)
                    maxPoint2 = point;

            }

            float gap = 0.0f;
            if ((minPoint2 >= minPoint1 && minPoint2 <= maxPoint1) ||//min2 is inside 1
                (maxPoint1 >= minPoint2 && maxPoint1 <= maxPoint2))  //max1 is inside 2
                gap = minPoint2 - maxPoint1;
            else if ((maxPoint2 >= minPoint1 && maxPoint2 <= maxPoint1) ||//max2 is inside 1
                     (minPoint1 >= minPoint2 && minPoint1 <= maxPoint2))  //min1 is inside 2
                gap = maxPoint2 - minPoint1;
            else
                return false;

            if (fabs(gap) < fabs(minGap)) {

                minGap = gap;
                least.x = unitNormal.x * minGap;
                least.y = unitNormal.y * minGap;

            }

        }

        return true;

    }

    bool BoundingShape::collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least, const sf::Transformable &globalTrans1, const sf::Transformable &globalTrans2) const {

        if (!(dynamic_cast<const sf::CircleShape *>(&poly1))) {

            std::cerr << "collisdes_ctp(): poly1 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();

        }
        if (dynamic_cast<const sf::CircleShape *>(&poly2)) {

            std::cerr << "collisdes_ctp(): poly2 is a circle not a polygon." << std::endl;
            throw std::bad_typeid();

        }

        const sf::CircleShape &circle = dynamic_cast<const sf::CircleShape &>(poly1);
        float eps = std::numeric_limits<float>::epsilon();
        if (fabs(circle.getScale().x - circle.getScale().y) >= eps ||
            fabs(globalTrans1.getScale().x - globalTrans1.getScale().y) >= eps)
            return this->collides_ptp(dynamic_cast<const sf::Shape &>(this->approximateCircle(circle, globalTrans1)), poly2, least, globalTrans1, globalTrans2);

        sf::Vector2f center = globalTrans1.getTransform().transformPoint(circle.getTransform().transformPoint(sf::Vector2f(circle.getRadius(), circle.getRadius())));
        float inf = std::numeric_limits<float>::infinity();
        float minDist = inf;
        sf::Vector2f circleNormal;

        least.x = inf;
        least.y = inf;
        float minGap = inf;
        float globalR = circle.getRadius() * circle.getScale().x * globalTrans1.getScale().x;
        uint32_t normalsLen = poly2.getPointCount() + 1;
        std::vector<sf::Vector2f> unitNormals(normalsLen);

        for (uint32_t i = 0; i < poly2.getPointCount(); i++) {

            sf::Vector2f currentVertex = globalTrans2.getTransform().transformPoint(poly2.getTransform().transformPoint(poly2.getPoint(i)));
            float xDiff = (currentVertex.x - center.x);
            float yDiff = (currentVertex.y - center.y);
            float distance = xDiff * xDiff + yDiff * yDiff;
            if (distance < minDist) {

                minDist = distance;
                circleNormal.x = xDiff;
                circleNormal.y = yDiff;
                float mag = static_cast<float>(sqrt(distance));
                circleNormal.x /= mag;
                circleNormal.y /= mag;

            }

            unitNormals.push_back(calculateUnitNormal(poly2, i, globalTrans2));

        }
        unitNormals.push_back(circleNormal);

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
            for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

                float point = projectPoint(poly2, unitNormal, k, globalTrans2);
                if (point < minPoint2)
                    minPoint2 = point;
                if (point > maxPoint2)
                    maxPoint2 = point;

            }

            float gap = 0.0f;
            if ((minPoint2 >= minPoint1 && minPoint2 <= maxPoint1) ||//min2 is inside 1
                (maxPoint1 >= minPoint2 && maxPoint1 <= maxPoint2))  //max1 is inside 2
                gap = minPoint2 - maxPoint1;
            else if ((maxPoint2 >= minPoint1 && maxPoint2 <= maxPoint1) ||//max2 is inside 1
                     (minPoint1 >= minPoint2 && minPoint1 <= maxPoint2))  //min1 is inside 2
                gap = maxPoint2 - minPoint1;
            else
                return false;

            if (fabs(gap) < fabs(minGap)) {

                minGap = gap;
                least.x = unitNormal.x * minGap;
                least.y = unitNormal.y * minGap;

            }

        }

        return true;

    }

    bool BoundingShape::collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least, const sf::Transformable &globalTrans1, const sf::Transformable &globalTrans2) const {

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
        float eps = std::numeric_limits<float>::epsilon();
        if ((fabs(circle1.getScale().x - circle1.getScale().y) >= eps ||
             fabs(globalTrans1.getScale().x - globalTrans1.getScale().y) >= eps) &&
            (fabs(circle2.getScale().x - circle2.getScale().y) >= eps ||
             fabs(globalTrans2.getScale().x - globalTrans2.getScale().y)))
            return this->collides_ptp(dynamic_cast<const sf::Shape &>(this->approximateCircle(circle1, globalTrans1)), dynamic_cast<const sf::Shape &>(this->approximateCircle(circle2, globalTrans2)), least, globalTrans1, globalTrans2);

        else if (!(fabs(circle1.getScale().x - circle1.getScale().y) >= eps ||
                   fabs(globalTrans1.getScale().x - globalTrans1.getScale().y) >= eps) &&
                 (fabs(circle2.getScale().x - circle2.getScale().y) >= eps ||
                  fabs(globalTrans2.getScale().x - globalTrans2.getScale().y) >= eps))
            return this->collides_ctp(poly1, dynamic_cast<const sf::Shape &>(this->approximateCircle(circle2, globalTrans2)), least, globalTrans1, globalTrans2);
        else if ((fabs(circle1.getScale().x - circle1.getScale().y) >= eps ||
                  fabs(globalTrans1.getScale().x - globalTrans1.getScale().y) >= eps) &&
                 !(fabs(circle2.getScale().x - circle2.getScale().y) >= eps ||
                   fabs(globalTrans2.getScale().x - globalTrans2.getScale().y) >= eps)) {
            bool r = this->collides_ctp(poly2, dynamic_cast<const sf::Shape &>(this->approximateCircle(circle1, globalTrans1)), least, globalTrans2, globalTrans1);
            least.x = -least.x;
            least.y = -least.y;

            return r;

        }

        sf::Vector2f center1 = globalTrans1.getTransform().transformPoint(circle1.getTransform().transformPoint(sf::Vector2f(circle1.getRadius(), circle1.getRadius())));
        sf::Vector2f center2 = globalTrans2.getTransform().transformPoint(circle2.getTransform().transformPoint(sf::Vector2f(circle2.getRadius(), circle2.getRadius())));

        float xDiff = (center2.x - center1.x);
        float yDiff = (center2.y - center1.y);
        float dist = xDiff * xDiff + yDiff * yDiff;
        float globalR1 = circle1.getRadius() * circle1.getScale().x * globalTrans1.getScale().x;
        float globalR2 = circle2.getRadius() * circle2.getScale().x * globalTrans2.getScale().x;
        float rSum = globalR1 + globalR2;
        if (dist <= (rSum * rSum)) {

            //Get both vectors
            sf::Vector2f centerVect1(xDiff, yDiff);
            sf::Vector2f centerVect2(center1.x - center2.x, center1.y - center2.y);

            //calculate Magnitudes
            float centerVectMag1 = static_cast<float>(sqrt(centerVect1.x * centerVect1.x + centerVect1.y * centerVect1.y));
            float centerVectMag2 = static_cast<float>(sqrt(centerVect2.x * centerVect2.x + centerVect2.y * centerVect2.y));

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

    bool BoundingShape::collides(const BoundingShape &bs, sf::Vector2f &least, const sf::Transformable &globalTrans1, const sf::Transformable &globalTrans2) const {

        least.x = 0.0f;
        least.y = 0.0f;
        bool isCollide = false;
        for (std::vector<sf::Shape *>::const_iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            for (uint32_t i = 0; i < bs.getNumOfShapes(); i++) {

                sf::Shape *s0 = (*it);
                const sf::Shape *s1 = bs.getShape(i);
                //Circle to Circle
                sf::Vector2f v(0.0f, 0.0f);
                if ((dynamic_cast<const sf::CircleShape *>(s0)) &&
                    (dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctc(*s0, *s1, v, globalTrans1, globalTrans2)) {

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
                    if (this->collides_ctp(*s0, *s1, v, globalTrans1, globalTrans2)) {

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
                    if (this->collides_ctp(*s1, *s0, v, globalTrans2, globalTrans1)) {

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
                    if (this->collides_ptp(*s0, *s1, v, globalTrans1, globalTrans2)) {

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
