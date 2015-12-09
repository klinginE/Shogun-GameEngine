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

}
