#include<BoundingShape.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>

void testBoundingShape() {

    //test init
    std::cout << "TESTING INIT" << std::endl;
    sg::BoundingShape bs0;
    std::cout << "bs0 number of shapes: " << bs0.getNumOfShapes() << std::endl;
    std::cout << std::endl;

    //test get invalid shape
    std::cout << "TESTING GET 10th shape" << std::endl;
    const sf::Shape *badShape = bs0.getShape(9);
    if (badShape == NULL)
        std::cout << "success!, shape is NULL" << std::endl;
    else
        std::cout << "failure!" << std::endl;
    std::cout << std::endl;

    //test add shape
    std::cout << "TESTING ADD SHAPE" << std::endl;
    sf::ConvexShape shape0(4);
    shape0.setPoint(0, sf::Vector2f(-5.0f, -5.0f));
    shape0.setPoint(1, sf::Vector2f(5.0f, -5.0f));
    shape0.setPoint(2, sf::Vector2f(5.0f, 5.0f));
    shape0.setPoint(3, sf::Vector2f(-5.0f, 5.0f));
    int index = bs0.addShape(shape0);
    std::cout << "Added index: " << index << std::endl;
    std::cout << "bs0 number of shapes: " << bs0.getNumOfShapes() << std::endl;
    std::cout << std::endl;

    //test get valid shape
    std::cout << "TESTING GET 0th SHAPE" << std::endl;
    const sf::Shape *goodShape = bs0.getShape(0);
    if (goodShape == &shape0)
        std::cout << "success!, addedShape is same as shape0" << std::endl;
    else
        std::cout << "failure!" << std::endl;
    std::cout << std::endl;

    //test remove invalid shape
    std::cout << "TESTING REMOVE 10th SHAPE" << std::endl;
    badShape = bs0.removeShape(9);
    if (badShape == NULL)
        std::cout << "success!, shape is NULL" << std::endl;
    else
        std::cout << "failure!" << std::endl;
    std::cout << std::endl;

    //test remove valid shape
    std::cout << "TESTING REMOVE 0th SHAPE" << std::endl;
    sf::Shape *removedShape = bs0.removeShape(0);
    if (removedShape == &shape0)
        std::cout << "success!, removedShape is same as shape0" << std::endl;
    else
        std::cout << "failure!" << std::endl;
    std::cout << std::endl;

    //test set origin (float, float) with no shapes
    std::cout << "TESTING SET ORIGIN (float, float) with no shapes" << std::endl;
    bs0.setOrigin(5.0f, 7.0f);
    std::cout << "Origin.x: " << bs0.getOrigin().x << ", Origin.y: " << bs0.getOrigin().y << std::endl << std::endl;

    //test set origin (sf::Vector2f) with no shapes
    std::cout << "TESTING SET ORIGIN (sf::Vector2f) with no shapes" << std::endl;
    bs0.setOrigin(sf::Vector2f(5.0f, 7.0f));
    std::cout << "Origin.x: " << bs0.getOrigin().x << ", Origin.y: " << bs0.getOrigin().y << std::endl << std::endl;

    //test set position (float, float) with no shapes
    std::cout << "TESTING SET POSITION (float, float) with no shapes" << std::endl;
    bs0.setPosition(9.0f, 2.0f);
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl << std::endl;

    //test set position (sf::Vector2f) with no shapes
    std::cout << "TESTING SET POSITION (sf::Vector2f) with no shapes" << std::endl;
    bs0.setPosition(sf::Vector2f(9.0f, 2.0f));
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl << std::endl;

    //test move (float, float) with no shapes
    std::cout << "TESTING MOVE (float, float) with no shapes" << std::endl;
    bs0.move(1.0f, 3.0f);
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl << std::endl;

    //test move (sf::Vector2f) with no shapes
    std::cout << "TESTING MOVE (sf::Vector2f) with no shapes" << std::endl;
    bs0.move(sf::Vector2f(1.0f, 3.0f));
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl << std::endl;

    //test set rotation (float) with no shapes
    std::cout << "TESTING SET ROTATION (float, float) with no shapes" << std::endl;
    bs0.setRotation(15.0f);
    std::cout << "Rotation: " << bs0.getRotation() << std::endl << std::endl;

    //test rotate (float) with no shapes
    std::cout << "TESTING ROTATE (float) with no shapes" << std::endl;
    bs0.rotate(30.0f);
    std::cout << "Rotation: " << bs0.getRotation() << std::endl << std::endl;

    //test set scale (float, float) with no shapes
    std::cout << "TESTING SET SCALE (float, float) with no shapes" << std::endl;
    bs0.setScale(2.0f, 3.0f);
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl << std::endl;

    //test set scale (sf::Vector2f) with no shapes
    std::cout << "TESTING SET SCALE (sf::Vector2f) with no shapes" << std::endl;
    bs0.setScale(sf::Vector2f(5.0f, 4.0f));
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl << std::endl;

    //test scale (float, float) with no shapes
    std::cout << "TESTING SCALE (float, float) with no shapes" << std::endl;
    bs0.scale(1.0f, 0.5f);
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl << std::endl;

    //test scale (sf::Vector2f) with no shapes
    std::cout << "TESTING SCALE (sf::Vector2f) with no shapes" << std::endl;
    bs0.scale(sf::Vector2f(2.0f, 1.0f));
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl << std::endl;

    //test local bounds without shapes
    std::cout << "TESTING local bounds without shapes" << std::endl;
    sf::FloatRect fr = bs0.getLocalBounds();
    std::cout << "bounds.left:    " << fr.left << std::endl;
    std::cout << "bounds.top:     " << fr.top << std::endl;
    std::cout << "bounds.width:   " << fr.width << std::endl;
    std::cout << "bounds.height:  " << fr.height << std::endl << std::endl;

    //test global bounds without shapes
    std::cout << "TESTING global bounds without shapes" << std::endl;
    fr = bs0.getGlobalBounds();
    std::cout << "bounds.left:    " << fr.left << std::endl;
    std::cout << "bounds.top:     " << fr.top << std::endl;
    std::cout << "bounds.width:   " << fr.width << std::endl;
    std::cout << "bounds.height:  " << fr.height << std::endl << std::endl;

    bs0.setOrigin(0.0f, 0.0f);
    bs0.setPosition(0.0f, 0.0f);
    bs0.setRotation(0.0f);
    bs0.setScale(1.0f, 1.0f);
    bs0.addShape(*removedShape);

    sf::ConvexShape shape1(4);
    shape1.setPoint(0, sf::Vector2f(-5.0f, -5.0f));
    shape1.setPoint(1, sf::Vector2f(5.0f, -5.0f));
    shape1.setPoint(2, sf::Vector2f(5.0f, 5.0f));
    shape1.setPoint(3, sf::Vector2f(-5.0f, 5.0f));
    bs0.addShape(shape1);

    sf::ConvexShape shape2(4);
    shape2.setPoint(0, sf::Vector2f(-5.0f, -5.0f));
    shape2.setPoint(1, sf::Vector2f(5.0f, -5.0f));
    shape2.setPoint(2, sf::Vector2f(5.0f, 5.0f));
    shape2.setPoint(3, sf::Vector2f(-5.0f, 5.0f));
    bs0.addShape(shape2);

    //test set origin (float, float) with shapes
    std::cout << "TESTING SET ORIGIN (float, float) with shapes" << std::endl;
    bs0.setOrigin(5.0f, 7.0f);
    std::cout << "Origin.x: " << bs0.getOrigin().x << ", Origin.y: " << bs0.getOrigin().y << std::endl;
    std::cout << "shape 0 Origin.x: " << bs0.getShape(0)->getOrigin().x << ", shape 0 Origin.y: " << bs0.getShape(0)->getOrigin().y << std::endl;
    std::cout << "shape 1 Origin.x: " << bs0.getShape(1)->getOrigin().x << ", shape 1 Origin.y: " << bs0.getShape(1)->getOrigin().y << std::endl;
    std::cout << "shape 2 Origin.x: " << bs0.getShape(2)->getOrigin().x << ", shape 2 Origin.y: " << bs0.getShape(2)->getOrigin().y << std::endl;
    std::cout << "shape 0 trans Origin.x: " << bs0.getShape(0)->getOrigin().x + bs0.getOrigin().x << ", shape 0 trans Origin.y: " << bs0.getShape(0)->getOrigin().y + bs0.getOrigin().y << std::endl;
    std::cout << "shape 1 trans Origin.x: " << bs0.getShape(1)->getOrigin().x + bs0.getOrigin().x << ", shape 1 trans Origin.y: " << bs0.getShape(1)->getOrigin().y + bs0.getOrigin().y << std::endl;
    std::cout << "shape 0 trans Origin.x: " << bs0.getShape(2)->getOrigin().x + bs0.getOrigin().x << ", shape 2 trans Origin.y: " << bs0.getShape(2)->getOrigin().y + bs0.getOrigin().y << std::endl << std::endl;

    //test set origin (sf::Vector2f) with shapes
    std::cout << "TESTING SET ORIGIN (sf::Vector2f) with shapes" << std::endl;
    bs0.setOrigin(sf::Vector2f(5.0f, 7.0f));
    std::cout << "Origin.x: " << bs0.getOrigin().x << ", Origin.y: " << bs0.getOrigin().y << std::endl;
    std::cout << "shape 0 Origin.x: " << bs0.getShape(0)->getOrigin().x << ", shape 0 Origin.y: " << bs0.getShape(0)->getOrigin().y << std::endl;
    std::cout << "shape 1 Origin.x: " << bs0.getShape(1)->getOrigin().x << ", shape 1 Origin.y: " << bs0.getShape(1)->getOrigin().y << std::endl;
    std::cout << "shape 2 Origin.x: " << bs0.getShape(2)->getOrigin().x << ", shape 2 Origin.y: " << bs0.getShape(2)->getOrigin().y << std::endl;
    std::cout << "shape 0 trans Origin.x: " << bs0.getShape(0)->getOrigin().x + bs0.getOrigin().x << ", shape 0 trans Origin.y: " << bs0.getShape(0)->getOrigin().y + bs0.getOrigin().y << std::endl;
    std::cout << "shape 1 trans Origin.x: " << bs0.getShape(1)->getOrigin().x + bs0.getOrigin().x << ", shape 1 trans Origin.y: " << bs0.getShape(1)->getOrigin().y + bs0.getOrigin().y << std::endl;
    std::cout << "shape 0 trans Origin.x: " << bs0.getShape(2)->getOrigin().x + bs0.getOrigin().x << ", shape 2 trans Origin.y: " << bs0.getShape(2)->getOrigin().y + bs0.getOrigin().y << std::endl << std::endl;

    //test set position (float, float) with shapes
    std::cout << "TESTING SET POSITION (float, float) with shapes" << std::endl;
    bs0.setPosition(9.0f, 2.0f);
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl;
    std::cout << "shape 0 Position.x: " << bs0.getShape(0)->getPosition().x << ", shape 0 Position.y: " << bs0.getShape(0)->getPosition().y << std::endl;
    std::cout << "shape 1 Position.x: " << bs0.getShape(1)->getPosition().x << ", shape 1 Position.y: " << bs0.getShape(1)->getPosition().y << std::endl;
    std::cout << "shape 2 Position.x: " << bs0.getShape(2)->getPosition().x << ", shape 2 Position.y: " << bs0.getShape(2)->getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(0)->getPosition().x + bs0.getPosition().x << ", shape 0 trans Position.y: " << bs0.getShape(0)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 1 trans Position.x: " << bs0.getShape(1)->getPosition().x + bs0.getPosition().x << ", shape 1 trans Position.y: " << bs0.getShape(1)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(2)->getPosition().x + bs0.getPosition().x << ", shape 2 trans Position.y: " << bs0.getShape(2)->getPosition().y + bs0.getPosition().y << std::endl << std::endl;

    //test set position (sf::Vector2f) with shapes
    std::cout << "TESTING SET POSITION (sf::Vector2f) with no shapes" << std::endl;
    bs0.setPosition(sf::Vector2f(9.0f, 2.0f));
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl;
    std::cout << "shape 0 Position.x: " << bs0.getShape(0)->getPosition().x << ", shape 0 Position.y: " << bs0.getShape(0)->getPosition().y << std::endl;
    std::cout << "shape 1 Position.x: " << bs0.getShape(1)->getPosition().x << ", shape 1 Position.y: " << bs0.getShape(1)->getPosition().y << std::endl;
    std::cout << "shape 2 Position.x: " << bs0.getShape(2)->getPosition().x << ", shape 2 Position.y: " << bs0.getShape(2)->getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(0)->getPosition().x + bs0.getPosition().x << ", shape 0 trans Position.y: " << bs0.getShape(0)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 1 trans Position.x: " << bs0.getShape(1)->getPosition().x + bs0.getPosition().x << ", shape 1 trans Position.y: " << bs0.getShape(1)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(2)->getPosition().x + bs0.getPosition().x << ", shape 2 trans Position.y: " << bs0.getShape(2)->getPosition().y + bs0.getPosition().y << std::endl << std::endl;

    //test move (float, float) with shapes
    std::cout << "TESTING MOVE (float, float) with shapes" << std::endl;
    bs0.move(1.0f, 3.0f);
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl;
    std::cout << "shape 0 Position.x: " << bs0.getShape(0)->getPosition().x << ", shape 0 Position.y: " << bs0.getShape(0)->getPosition().y << std::endl;
    std::cout << "shape 1 Position.x: " << bs0.getShape(1)->getPosition().x << ", shape 1 Position.y: " << bs0.getShape(1)->getPosition().y << std::endl;
    std::cout << "shape 2 Position.x: " << bs0.getShape(2)->getPosition().x << ", shape 2 Position.y: " << bs0.getShape(2)->getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(0)->getPosition().x + bs0.getPosition().x << ", shape 0 trans Position.y: " << bs0.getShape(0)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 1 trans Position.x: " << bs0.getShape(1)->getPosition().x + bs0.getPosition().x << ", shape 1 trans Position.y: " << bs0.getShape(1)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(2)->getPosition().x + bs0.getPosition().x << ", shape 2 trans Position.y: " << bs0.getShape(2)->getPosition().y + bs0.getPosition().y << std::endl << std::endl;

    //test move (sf::Vector2f) with shapes
    std::cout << "TESTING MOVE (sf::Vector2f) with shapes" << std::endl;
    bs0.move(sf::Vector2f(1.0f, 3.0f));
    std::cout << "Position.x: " << bs0.getPosition().x << ", Position.y: " << bs0.getPosition().y << std::endl;
    std::cout << "shape 0 Position.x: " << bs0.getShape(0)->getPosition().x << ", shape 0 Position.y: " << bs0.getShape(0)->getPosition().y << std::endl;
    std::cout << "shape 1 Position.x: " << bs0.getShape(1)->getPosition().x << ", shape 1 Position.y: " << bs0.getShape(1)->getPosition().y << std::endl;
    std::cout << "shape 2 Position.x: " << bs0.getShape(2)->getPosition().x << ", shape 2 Position.y: " << bs0.getShape(2)->getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(0)->getPosition().x + bs0.getPosition().x << ", shape 0 trans Position.y: " << bs0.getShape(0)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 1 trans Position.x: " << bs0.getShape(1)->getPosition().x + bs0.getPosition().x << ", shape 1 trans Position.y: " << bs0.getShape(1)->getPosition().y + bs0.getPosition().y << std::endl;
    std::cout << "shape 0 trans Position.x: " << bs0.getShape(2)->getPosition().x + bs0.getPosition().x << ", shape 2 trans Position.y: " << bs0.getShape(2)->getPosition().y + bs0.getPosition().y << std::endl << std::endl;

    //test set rotation (float) with shapes
    std::cout << "TESTING SET ROTATION (float, float) with shapes" << std::endl;
    bs0.setRotation(15.0f);
    std::cout << "Rotation: " << bs0.getRotation() << std::endl;
    std::cout << "shape 0 rotation: " << bs0.getShape(0)->getRotation() << std::endl;
    std::cout << "shape 1 rotation: " << bs0.getShape(1)->getRotation() << std::endl;
    std::cout << "shape 2 rotation: " << bs0.getShape(2)->getRotation() << std::endl;
    std::cout << "shape 0 trans rotation: " << bs0.getShape(0)->getRotation() + bs0.getRotation() << std::endl;
    std::cout << "shape 1 trans rotation: " << bs0.getShape(1)->getRotation() + bs0.getRotation() << std::endl;
    std::cout << "shape 2 trans rotation: " << bs0.getShape(2)->getRotation() + bs0.getRotation() << std::endl << std::endl;

    //test rotate (float) with shapes
    std::cout << "TESTING ROTATE (float) with shapes" << std::endl;
    bs0.rotate(30.0f);
    std::cout << "Rotation: " << bs0.getRotation() << std::endl;
    std::cout << "shape 0 rotation: " << bs0.getShape(0)->getRotation() << std::endl;
    std::cout << "shape 1 rotation: " << bs0.getShape(1)->getRotation() << std::endl;
    std::cout << "shape 2 rotation: " << bs0.getShape(2)->getRotation() << std::endl;
    std::cout << "shape 0 trans rotation: " << bs0.getShape(0)->getRotation() + bs0.getRotation() << std::endl;
    std::cout << "shape 1 trans rotation: " << bs0.getShape(1)->getRotation() + bs0.getRotation() << std::endl;
    std::cout << "shape 2 trans rotation: " << bs0.getShape(2)->getRotation() + bs0.getRotation() << std::endl << std::endl;

    //test set scale (float, float) with shapes
    std::cout << "TESTING SET SCALE (float, float) with shapes" << std::endl;
    bs0.setScale(2.0f, 3.0f);
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl;
    std::cout << "shape 0 scale.x: " << bs0.getShape(0)->getScale().x << ", shape 0 scale.y: " << bs0.getShape(0)->getScale().y << std::endl;
    std::cout << "shape 1 scale.x: " << bs0.getShape(1)->getScale().x << ", shape 1 scale.y: " << bs0.getShape(1)->getScale().y << std::endl;
    std::cout << "shape 2 scale.x: " << bs0.getShape(2)->getScale().x << ", shape 2 scale.y: " << bs0.getShape(2)->getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(0)->getScale().x * bs0.getScale().x << ", shape 0 trans scale.y: " << bs0.getShape(0)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 1 trans scale.x: " << bs0.getShape(1)->getScale().x * bs0.getScale().x << ", shape 1 trans scale.y: " << bs0.getShape(1)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(2)->getScale().x * bs0.getScale().x << ", shape 2 trans scale.y: " << bs0.getShape(2)->getScale().y * bs0.getScale().y << std::endl << std::endl;

    //test set scale (sf::Vector2f) with shapes
    std::cout << "TESTING SET SCALE (sf::Vector2f) with shapes" << std::endl;
    bs0.setScale(sf::Vector2f(5.0f, 4.0f));
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl;
    std::cout << "shape 0 scale.x: " << bs0.getShape(0)->getScale().x << ", shape 0 scale.y: " << bs0.getShape(0)->getScale().y << std::endl;
    std::cout << "shape 1 scale.x: " << bs0.getShape(1)->getScale().x << ", shape 1 scale.y: " << bs0.getShape(1)->getScale().y << std::endl;
    std::cout << "shape 2 scale.x: " << bs0.getShape(2)->getScale().x << ", shape 2 scale.y: " << bs0.getShape(2)->getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(0)->getScale().x * bs0.getScale().x << ", shape 0 trans scale.y: " << bs0.getShape(0)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 1 trans scale.x: " << bs0.getShape(1)->getScale().x * bs0.getScale().x << ", shape 1 trans scale.y: " << bs0.getShape(1)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(2)->getScale().x * bs0.getScale().x << ", shape 2 trans scale.y: " << bs0.getShape(2)->getScale().y * bs0.getScale().y << std::endl << std::endl;

    //test scale (float, float) with shapes
    std::cout << "TESTING SCALE (float, float) with shapes" << std::endl;
    bs0.scale(1.0f, 0.5f);
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl;
    std::cout << "shape 0 scale.x: " << bs0.getShape(0)->getScale().x << ", shape 0 scale.y: " << bs0.getShape(0)->getScale().y << std::endl;
    std::cout << "shape 1 scale.x: " << bs0.getShape(1)->getScale().x << ", shape 1 scale.y: " << bs0.getShape(1)->getScale().y << std::endl;
    std::cout << "shape 2 scale.x: " << bs0.getShape(2)->getScale().x << ", shape 2 scale.y: " << bs0.getShape(2)->getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(0)->getScale().x * bs0.getScale().x << ", shape 0 trans scale.y: " << bs0.getShape(0)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 1 trans scale.x: " << bs0.getShape(1)->getScale().x * bs0.getScale().x << ", shape 1 trans scale.y: " << bs0.getShape(1)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(2)->getScale().x * bs0.getScale().x << ", shape 2 trans scale.y: " << bs0.getShape(2)->getScale().y * bs0.getScale().y << std::endl << std::endl;

    //test scale (sf::Vector2f) with shapes
    std::cout << "TESTING SCALE (sf::Vector2f) with shapes" << std::endl;
    bs0.scale(sf::Vector2f(2.0f, 1.0f));
    std::cout << "Scale.x: " << bs0.getScale().x << ", Scale.y: " << bs0.getScale().y << std::endl;
    std::cout << "shape 0 scale.x: " << bs0.getShape(0)->getScale().x << ", shape 0 scale.y: " << bs0.getShape(0)->getScale().y << std::endl;
    std::cout << "shape 1 scale.x: " << bs0.getShape(1)->getScale().x << ", shape 1 scale.y: " << bs0.getShape(1)->getScale().y << std::endl;
    std::cout << "shape 2 scale.x: " << bs0.getShape(2)->getScale().x << ", shape 2 scale.y: " << bs0.getShape(2)->getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(0)->getScale().x * bs0.getScale().x << ", shape 0 trans scale.y: " << bs0.getShape(0)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 1 trans scale.x: " << bs0.getShape(1)->getScale().x * bs0.getScale().x << ", shape 1 trans scale.y: " << bs0.getShape(1)->getScale().y * bs0.getScale().y << std::endl;
    std::cout << "shape 0 trans scale.x: " << bs0.getShape(2)->getScale().x * bs0.getScale().x << ", shape 2 trans scale.y: " << bs0.getShape(2)->getScale().y * bs0.getScale().y << std::endl << std::endl;

    //test local bounds with shapes
    std::cout << "TESTING local bounds with shapes" << std::endl;
    fr = bs0.getLocalBounds();
    std::cout << "bounds.left:    " << fr.left << std::endl;
    std::cout << "bounds.top:     " << fr.top << std::endl;
    std::cout << "bounds.width:   " << fr.width << std::endl;
    std::cout << "bounds.height:  " << fr.height << std::endl << std::endl;

    //test global bounds with shapes
    std::cout << "TESTING global bounds with shapes" << std::endl;
    fr = bs0.getGlobalBounds();
    std::cout << "bounds.left:    " << fr.left << std::endl;
    std::cout << "bounds.top:     " << fr.top << std::endl;
    std::cout << "bounds.width:   " << fr.width << std::endl;
    std::cout << "bounds.height:  " << fr.height << std::endl << std::endl;

}

int main() {

    testBoundingShape();

    return 0;

}
