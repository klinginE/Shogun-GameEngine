#include"BoundingShape.hpp"

namespace sg {

    BoundingShape::BoundingShape() {



    }

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
            if ((br.left + br.width) > br.width)
                bounds.width = (br.left + br.width);
            if ((br.top + br.height) > br.height)
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

}
