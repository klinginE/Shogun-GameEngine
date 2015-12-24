//C++ includes
#include<stdexcept>
#include<typeinfo>
#include<iostream>

//SHOGUN includes
#include"BoundingShape.hpp"

namespace sg {

    BoundingShape::BoundingShape() {}

    BoundingShape::~BoundingShape() {

        this->shapes.clear();

    }

    std::vector<const sf::Shape *>::size_type BoundingShape::getNumOfShapes() const {

        return this->shapes.size();

    }

    const sf::Shape *BoundingShape::getShape(uint32_t idx) const {

        if (idx >= this->getNumOfShapes())
            return NULL;
        return this->shapes[idx];

    }

    std::vector<const sf::Shape *>::size_type BoundingShape::addShape(const sf::Shape &newShape) {

        this->shapes.push_back(&newShape);
        return (this->getNumOfShapes() - 1);

    }

    const sf::Shape *BoundingShape::removeShape(uint32_t idx) {

        if (idx >= this->getNumOfShapes())
            return NULL;

        const sf::Shape *s = this->shapes[idx];
        this->shapes.erase(this->shapes.begin() + idx);

        return s;

    }

    sf::FloatRect BoundingShape::getShapeBounds(bool useLocal) const {

        float inf = std::numeric_limits<float>::infinity();
        sf::FloatRect bounds(inf, inf, -inf, -inf);
        for (std::vector<const sf::Shape *>::const_iterator it = this->shapes.begin(); it != this->shapes.end(); ++it) {

            const sf::Shape *s = (*it);
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

    sf::Vector2f BoundingShape::calculateUnitNormal(const sf::Shape &poly, uint32_t i) const {

        uint32_t j = (i + 1) % poly.getPointCount();
        sf::Vector2f currentVertex(poly.getPoint(i).x + poly.getPosition().x, poly.getPoint(i).y + poly.getPosition().y);
        sf::Vector2f adjacentVertex(poly.getPoint(j).x + poly.getPosition().x, poly.getPoint(j).y + poly.getPosition().y);
        sf::Vector2f unitNormal(adjacentVertex.x - currentVertex.x, adjacentVertex.y - currentVertex.y);
        float magnitude = static_cast<float>(std::sqrt(unitNormal.x * unitNormal.x + unitNormal.y * unitNormal.y));
        unitNormal.x /= magnitude;
        unitNormal.y /= magnitude;
        //Rotate by 90
        float tempX = unitNormal.x;
        unitNormal.x = -1.0f * unitNormal.y;
        unitNormal.y = tempX;

        return unitNormal;

    }

    float BoundingShape::projectPoint(const sf::Shape &poly, const sf::Vector2f &unitNormal, uint32_t k) const {

        sf::Vector2f vertex(poly.getPoint(k).x + poly.getPosition().x, poly.getPoint(k).y + poly.getPosition().y);
        float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;

        return point;

    }

    bool BoundingShape::collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least) const {

        if (dynamic_cast<const sf::CircleShape *>(&poly1)) {

            std::cerr << "collides_ptp(): poly1 is circle shape not polygon." << std::endl;
            throw std::bad_typeid();

        }
        if (dynamic_cast<const sf::CircleShape *>(&poly2)) {

            std::cerr << "collides_ptp(): poly2 is circle shape not polygon." << std::endl;
            throw std:: bad_typeid();

        }

        float inf = std::numeric_limits<float>::infinity();
        least.x  = inf;
        least.y = inf;
        float minGap = inf;
        uint32_t normalsLen = poly1.getPointCount() + poly2.getPointCount();
        std::vector<sf::Vector2f> unitNormals;

        for (uint32_t i = 0; i < poly1.getPointCount(); i++)
            unitNormals.push_back(calculateUnitNormal(poly1, i));

        for (uint32_t i = 0; i < poly2.getPointCount(); i++)
            unitNormals.push_back(calculateUnitNormal(poly2, i));

        for (uint32_t i = 0; i < normalsLen; i++) {

            sf::Vector2f unitNormal = unitNormals[i];
 
            float minPoint1 = inf;
            float maxPoint1 = -inf;
            for (uint32_t k = 0; k < poly1.getPointCount(); k++) {

                float point = projectPoint(poly1, unitNormal, k);
                if (point < minPoint1)
                    minPoint1 = point;
                if (point > maxPoint1)
                    maxPoint1 = point;

            }

            float minPoint2 = inf;
            float maxPoint2 = -inf;
            for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

                float point = projectPoint(poly2, unitNormal, k);
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

            if (std::fabs(gap) < std::fabs(minGap)) {

                minGap = gap;
                least.x = unitNormal.x * minGap;
                least.y = unitNormal.y * minGap;

            }

        }

        return true;

    }

    bool BoundingShape::collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least) const {

        if (!(dynamic_cast<const sf::CircleShape *>(&poly1))) {

            std::cerr << "collisdes_ctp(): poly1 is a polygon not a circle." << std::endl;
            throw std::bad_typeid();

        }
        if (dynamic_cast<const sf::CircleShape *>(&poly2)) {

            std::cerr << "collisdes_ctp(): poly2 is a circle not a polygon." << std::endl;
            throw std::bad_typeid();

        }

        const sf::CircleShape &circle = dynamic_cast<const sf::CircleShape &>(poly1);

        sf::Vector2f center(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());
        float inf = std::numeric_limits<float>::infinity();
        float minDist = inf;
        sf::Vector2f circleNormal;

        least.x = inf;
        least.y = inf;
        float minGap = inf;
        uint32_t normalsLen = poly2.getPointCount() + 1;
        std::vector<sf::Vector2f> unitNormals;

        for (uint32_t i = 0; i < poly2.getPointCount(); i++) {

            sf::Vector2f currentVertex(poly2.getPoint(i).x + poly2.getPosition().x, poly2.getPoint(i).y + poly2.getPosition().y);

            float xDiff = (currentVertex.x - center.x);
            float yDiff = (currentVertex.y - center.y);
            float distance = xDiff * xDiff + yDiff * yDiff;
            if (distance < minDist) {

                minDist = distance;
                circleNormal.x = xDiff;
                circleNormal.y = yDiff;
                float mag = static_cast<float>(std::sqrt(distance));
                circleNormal.x /= mag;
                circleNormal.y /= mag;

            }

            unitNormals.push_back(calculateUnitNormal(poly2, i));

        }
        unitNormals.push_back(circleNormal);

        for (uint32_t i = 0; i < normalsLen; i++) {

            sf::Vector2f unitNormal = unitNormals[i];

            float dot = center.x * unitNormal.x + center.y * unitNormal.y;
            float minPoint1 = dot - circle.getRadius();
            float maxPoint1 = dot + circle.getRadius();
            if (minPoint1 > maxPoint1) {

                float temp = minPoint1;
                minPoint1 = maxPoint1;
                maxPoint1 = temp;

            }

            float minPoint2 = inf;
            float maxPoint2 = -inf;
            for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

                float point = projectPoint(poly2, unitNormal, k);
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

            if (std::fabs(gap) < std::fabs(minGap)) {
    
                minGap = gap;
                least.x = unitNormal.x * minGap;
                least.y = unitNormal.y * minGap;

            }

        }

        return true;

    }

    bool BoundingShape::collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2, sf::Vector2f &least) const {

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

        sf::Vector2f center1(circle1.getPosition().x + circle1.getRadius(), circle1.getPosition().y + circle1.getRadius());
        sf::Vector2f center2(circle2.getPosition().x + circle2.getRadius(), circle2.getPosition().y + circle2.getRadius());

        float xDiff = (center2.x - center1.x);
        float yDiff = (center2.y - center1.y);
        float dist = xDiff * xDiff + yDiff * yDiff;
        float rSum = circle1.getRadius() + circle2.getRadius();
        if (dist <= (rSum * rSum)) {

            //Get both vectors
            sf::Vector2f centerVect1(xDiff, yDiff);
            sf::Vector2f centerVect2(center1.x - center2.x, center1.y - center2.y);

            //calculate Magnitudes
            float centerVectMag1 = static_cast<float>(std::sqrt(centerVect1.x * centerVect1.x + centerVect1.y * centerVect1.y));
            float centerVectMag2 = static_cast<float>(std::sqrt(centerVect2.x * centerVect2.x + centerVect2.y * centerVect2.y));

            //Locate Points on circles
            sf::Vector2f circlePoint1((centerVect1.x / centerVectMag1 * circle1.getRadius()) + center1.x,
                                      (centerVect1.y / centerVectMag1 * circle1.getRadius()) + center1.y);
            sf::Vector2f circlePoint2((centerVect2.x / centerVectMag2 * circle2.getRadius()) + center2.x,
                                      (centerVect2.y / centerVectMag2 * circle2.getRadius()) + center2.y);

            least.x = circlePoint2.x - circlePoint1.x;
            least.y = circlePoint2.y - circlePoint1.y;

            return true;

        }

        return false;

    }

    bool BoundingShape::collides(const BoundingShape &bs, sf::Vector2f &least) const {

        //float inf = std::numeric_limits<float>::infinity();
        //least.x = -inf;
        //least.y = -inf;
        least.x = 0.0f;
        least.y = 0.0f;
        bool isCollide = false;
        for (std::vector<const sf::Shape *>::const_iterator it = this->shapes.begin(); it != this->shapes.end(); ++it)
            for (uint32_t i = 0; i < bs.getNumOfShapes(); i++) {

                const sf::Shape *s0 = (*it);
                const sf::Shape *s1 = bs.getShape(i);
                //Circle to Circle
                sf::Vector2f v(0.0f, 0.0f);
                if ((dynamic_cast<const sf::CircleShape *>(s0)) &&
                    (dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctc(*s0, *s1, v)) {

                        isCollide = true;
                        if (std::fabs(v.x) > std::fabs(least.x))
                            least.x = v.x;
                        if (std::fabs(v.y) > std::fabs(least.y))
                            least.y = v.y;

                    }
                }
                //Circle to polygon
                else if ((dynamic_cast<const sf::CircleShape *>(s0)) &&
                         !(dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctp(*s0, *s1, v)) {

                        isCollide = true;
                        if (std::fabs(v.x) > std::fabs(least.x))
                            least.x = v.x;
                        if (std::fabs(v.y) > std::fabs(least.y))
                            least.y = v.y;

                    }
                }
                //polygon to circle
                else if (!(dynamic_cast<const sf::CircleShape *>(s0)) &&
                         (dynamic_cast<const sf::CircleShape *>(s1))) {
                    if (this->collides_ctp(*s1, *s0, v)) {

                        v.x = -v.x;
                        v.y = -v.y;
                        isCollide = true;
                        if (std::fabs(v.x) > std::fabs(least.x))
                            least.x = v.x;
                        if (std::fabs(v.y) > std::fabs(least.y))
                            least.y = v.y;

                    }
                }
                //polygon to polygon
                else {
                    if (this->collides_ptp(*s0, *s1, v)) {

                        isCollide = true;
                        std::cout << "vect.x: " << v.x << " vect.y: " << v.y << std::endl;
                        std::cout << "least.x: " << least.x << " vect.y: " << least.y << std::endl;
                        if (std::fabs(v.x) > std::fabs(least.x))
                            least.x = v.x;
                        if (std::fabs(v.y) > std::fabs(least.y))
                            least.y = v.y;

                    }
                }

            }

        return isCollide;

    }

}
