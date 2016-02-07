#include<BoundingShape.hpp>
#include<AnimatedSprite.hpp>
#include<GameLoop.hpp>
#include<GameState.hpp>
#include<StateManager.hpp>
#include<GameWindow.hpp>
#include<GameWorld.hpp>
#include<Entity.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include"TestEntityState.hpp"

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

void testAnimatedSprite() {

    //test initilization
    sg::AnimatedSprite as0 = sg::AnimatedSprite();
    std::cout << "TESTING initilization" << std::endl;
    std::cout << "Adress of sprite: " << &as0 << std::endl;
    std::cout << "Number of frames: " << as0.getNumOfFrames() << std::endl;
    std::cout << "Invalid bound: " << as0.getFrameBound(10) << std::endl;
    std::cout << "Invalid Rect: " << as0.getFrameRect(10) << std::endl;
    std::cout << "Frame Delay: " << as0.getFrameDelay().asSeconds() << std::endl;
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //test set frame delay
    as0.setFrameDelay(sf::seconds(10.0f));
    std::cout << "Frame Delay: " << as0.getFrameDelay().asSeconds() << std::endl;
    std::cout << "Updateing after 3 seconds while not playing and no frames" << std::endl;
    as0.update(sf::seconds(3.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    std::cout << "Updateing after 3 seconds while playing and no frames" << std::endl;
    as0.start();
    as0.update(sf::seconds(3.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //testing adding a frame
    sf::IntRect frameRect0 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds0 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    std::cout << "New Frame index:  " << as0.addFrame(frameRect0, frameBounds0) << std::endl;
    std::cout << "Number of frames: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Outside chane to frameRect0 top testing get FrameRect
    frameRect0.top = 2;
    std::cout << "Geting frame rect:" << std::endl;
    std::cout << "    left:   " << as0.getFrameRect(0)->left << std::endl;
    std::cout << "    top:    " << as0.getFrameRect(0)->top << std::endl;
    std::cout << "    width:  " << as0.getFrameRect(0)->width << std::endl;
    std::cout << "    height: " << as0.getFrameRect(0)->height << std::endl;
    std::cout << std::endl;

    //test get frame Bound
    const sf::Transformable *bound0 =  as0.getFrameBound(0);
    std::cout << "Addresses match: " << (dynamic_cast<void *>(&frameBounds0) == dynamic_cast<const void *>(bound0)) << std::endl;
    std::cout << std::endl;

    //test remove invalid frame
    std::cout << "Removing invalid frame" << std::endl;
    std::pair<sf::IntRect *, sf::Transformable *> removeFramePair = as0.removeFrame(10);
    std::cout << "removeFramePair.first:  " << removeFramePair.first << std::endl;
    std::cout << "removeFramePair.second: " << removeFramePair.second << std::endl;
    std::cout << std::endl;

    //test remove valid frame
    std::pair<sf::IntRect *, sf::Transformable *> removePair = as0.removeFrame(0);
    std::cout << "remove rect:   " << removePair.first << std::endl;
    std::cout << "remove bounds: " << removePair.second << std::endl;
    std::cout << "rect addresses match:   " << (&frameRect0 == removePair.first) << std::endl;
    std::cout << "bounds addresses match: " << (dynamic_cast<void *>(&frameBounds0) == dynamic_cast<void *>(removePair.second)) << std::endl;
    std::cout << std::endl;

    //Test update while playing with one frame
    as0.addFrame(*removePair.first, *removePair.second);
    std::cout << "Updateing after 3 seconds while playing and one frame" << std::endl;
    as0.update(sf::seconds(3.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //Test update while playing with one frame
    std::cout << "Updateing after 22 seconds while playing and one frame" << std::endl;
    as0.update(sf::seconds(22.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    std::cout << "Adding 4 more frames" << std::endl;
    sf::IntRect frameRect1 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds1 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect1, frameBounds1);
    sf::IntRect frameRect2 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds2 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect2, frameBounds2);
    sf::IntRect frameRect3 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds3 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect3, frameBounds3);
    sf::IntRect frameRect4 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds4 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect4, frameBounds4);
    std::cout << "Number of frame: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Test update while playing with five frames
    std::cout << "Updateing after 22 seconds while playing and two frame" << std::endl;
    as0.update(sf::seconds(22.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //Test transformations 5 frames
    std::cout << "Seting origin to 2.0f, 2.0f" << std::endl;
    as0.setOrigin(2.0f, 2.0f);
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    as0.setOrigin(sf::Vector2f(2.0f, 2.0f));
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    std::cout << "Seting position to 10.0f, 12.0f" << std::endl;
    as0.setPosition(10.0f, 12.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    as0.setPosition(sf::Vector2f(10.0f, 12.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by 2.0f, 2.0f" << std::endl;
    as0.move(2.0f, 2.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by -2.0f, -2.0f" << std::endl;
    as0.move(sf::Vector2f(-2.0f, -2.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Set rotation to 15.0f" << std::endl;
    as0.setRotation(15.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "Rotating by 30.0f" << std::endl;
    as0.rotate(30.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "set scale by 4.0f, 1.5f" << std::endl;
    as0.setScale(4.0f, 1.5f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    as0.setScale(sf::Vector2f(4.0f, 1.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 0.5f, 2.0f" << std::endl;
    as0.scale(0.5f, 2.0f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 2.0f, 0.5f" << std::endl;
    as0.scale(sf::Vector2f(2.0f, 0.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << std::endl;

    std::cout << "removing all but one frame and setting bounds0 back to 0" << std::endl;
    removePair = as0.removeFrame(0);
    as0.removeFrame(0);
    as0.removeFrame(0);
    as0.removeFrame(0);
    sf::Transformable *t = removePair.second;
    t->setOrigin(0.0f, 0.0f);
    t->setPosition(0.0f, 0.0f);
    t->setRotation(0.0f);
    t->setScale(1.0f, 1.0f);
    std::cout << "Frame count: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Test transformations 1 frames
    std::cout << "Seting origin to 2.0f, 2.0f" << std::endl;
    as0.setOrigin(2.0f, 2.0f);
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    as0.setOrigin(sf::Vector2f(2.0f, 2.0f));
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    std::cout << "Seting position to 10.0f, 12.0f" << std::endl;
    as0.setPosition(10.0f, 12.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    as0.setPosition(sf::Vector2f(10.0f, 12.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by 2.0f, 2.0f" << std::endl;
    as0.move(2.0f, 2.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by -2.0f, -2.0f" << std::endl;
    as0.move(sf::Vector2f(-2.0f, -2.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Set rotation to 15.0f" << std::endl;
    as0.setRotation(15.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "Rotating by 30.0f" << std::endl;
    as0.rotate(30.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "set scale by 4.0f, 1.5f" << std::endl;
    as0.setScale(4.0f, 1.5f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    as0.setScale(sf::Vector2f(4.0f, 1.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 0.5f, 2.0f" << std::endl;
    as0.scale(0.5f, 2.0f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 2.0f, 0.5f" << std::endl;
    as0.scale(sf::Vector2f(2.0f, 0.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << std::endl;

    std::cout << "removing last frame" << std::endl;
    as0.removeFrame(0);
    std::cout << "Number of Frames: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Test transformations 0 frames
    std::cout << "Seting origin to 2.0f, 2.0f" << std::endl;
    as0.setOrigin(2.0f, 2.0f);
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    as0.setOrigin(sf::Vector2f(2.0f, 2.0f));
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    std::cout << "Seting position to 10.0f, 12.0f" << std::endl;
    as0.setPosition(10.0f, 12.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    as0.setPosition(sf::Vector2f(10.0f, 12.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by 2.0f, 2.0f" << std::endl;
    as0.move(2.0f, 2.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by -2.0f, -2.0f" << std::endl;
    as0.move(sf::Vector2f(-2.0f, -2.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Set rotation to 15.0f" << std::endl;
    as0.setRotation(15.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "Rotating by 30.0f" << std::endl;
    as0.rotate(30.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "set scale by 4.0f, 1.5f" << std::endl;
    as0.setScale(4.0f, 1.5f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    as0.setScale(sf::Vector2f(4.0f, 1.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 0.5f, 2.0f" << std::endl;
    as0.scale(0.5f, 2.0f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 2.0f, 0.5f" << std::endl;
    as0.scale(sf::Vector2f(2.0f, 0.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << std::endl;

}

void testEntity() {

    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2u(600, 600),
                              sf::String("Test Elements"));
    sg::GameLoop::inst().getRenderWindow().setFramerateLimit(60);

    TestEntityState tes;
    sg::StateManager::inst().pushState(&tes);

    // Start gameloop
    sg::GameLoop::inst().start();

}

int main() {

    //testBoundingShape();
    //testAnimatedSprite();
    testEntity();

    return 0;

}
