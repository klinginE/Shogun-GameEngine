#include<BoundingShape.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>

int main() {

    sg::BoundingShape bs0;
    std::cout << "bs0 getNumOfShapes: " << bs0.getNumOfShapes() << std::endl;
    sf::ConvexShape s0;
    s0.setPosition(sf::Vector2f(8.0f, 0.0f));
    s0.setPointCount(4);
    s0.setPoint(0, sf::Vector2f(-2.0f, 0.0f));
    s0.setPoint(1, sf::Vector2f(2.0f, 0.0f));
    s0.setPoint(2, sf::Vector2f(10.0f, 10.0f));
    s0.setPoint(3, sf::Vector2f(-10.0f, 10.0f));
    s0.scale(sf::Vector2f(2.0f, 2.0f));
    bs0.addShape(s0);
    std::cout << bs0.getNumOfShapes() << std::endl;
    std::cout << "x: " << bs0.getShape(0)->getPoint(0).x << ", y: " << bs0.getShape(0)->getPoint(0).y << std::endl;
    std::cout << "x: " << bs0.getShape(0)->getPoint(1).x << ", y: " << bs0.getShape(0)->getPoint(1).y << std::endl;
    std::cout << "x: " << bs0.getShape(0)->getPoint(2).x << ", y: " << bs0.getShape(0)->getPoint(2).y << std::endl;
    std::cout << "x: " << bs0.getShape(0)->getPoint(3).x << ", y: " << bs0.getShape(0)->getPoint(3).y << std::endl << std::endl;

    sg::BoundingShape bs1;
    std::cout << "bs1 getNumOfShapes: " << bs1.getNumOfShapes() << std::endl;
    sf::ConvexShape s1;
    s1.setPosition(sf::Vector2f(0.0f, 0.0f));
    s1.setPointCount(4);
    s1.setPoint(0, sf::Vector2f(0.0f, 0.0f));
    s1.setPoint(1, sf::Vector2f(100.0f, 0.0f));
    s1.setPoint(2, sf::Vector2f(10.0f, 100.0f));
    s1.setPoint(3, sf::Vector2f(0.0f, 100.0f));
    bs1.addShape(s1);
    std::cout << "bs1 getNumOfShapes: " << bs1.getNumOfShapes() << std::endl;
    std::cout << "x: " << bs1.getShape(0)->getPoint(0).x << ", y: " << bs1.getShape(0)->getPoint(0).y << std::endl;
    std::cout << "x: " << bs1.getShape(0)->getPoint(1).x << ", y: " << bs1.getShape(0)->getPoint(1).y << std::endl;
    std::cout << "x: " << bs1.getShape(0)->getPoint(2).x << ", y: " << bs1.getShape(0)->getPoint(2).y << std::endl;
    std::cout << "x: " << bs1.getShape(0)->getPoint(3).x << ", y: " << bs1.getShape(0)->getPoint(3).y << std::endl;
    sf::Vector2f v1(0.0f, 0.0f);
    std::cout << "collides?: " << bs0.collides(bs1, v1) << std::endl;
    std::cout << "v1.x: " << v1.x << " v1.y: " << v1.y << std::endl << std::endl; 

    sf::CircleShape s2;
    s2.setPosition(sf::Vector2f(0.0f, 0.0f));
    s2.setRadius(20.0f);
    bs1.addShape(s2);
    std::cout << "bs1 getNumOfShapes: " << bs1.getNumOfShapes() << std::endl;
    const sf::ConvexShape rm = *dynamic_cast<const sf::ConvexShape *>(bs1.removeShape(0));
    std::cout << "bs1 getNumOfShapes: " << bs1.getNumOfShapes() << std::endl;
    std::cout << "rm.x: " << rm.getPoint(0).x << ", rm.y: " << rm.getPoint(0).y << std::endl;
    std::cout << "rm.x: " << rm.getPoint(1).x << ", rm.y: " << rm.getPoint(1).y << std::endl;
    std::cout << "rm.x: " << rm.getPoint(2).x << ", rm.y: " << rm.getPoint(2).y << std::endl;
    std::cout << "rm.x: " << rm.getPoint(3).x << ", rm.y: " << rm.getPoint(3).y << std::endl;
    std::cout << "bs1 addShape: " << bs1.addShape(rm) << std::endl;
    sf::Vector2f v2(0.0f, 0.0f);
    std::cout << "collides b0_to_b1?: " << bs0.collides(bs1, v2) << std::endl;
    std::cout << "v2.x: " << v2.x << " v2.y: " << v2.y << std::endl;
    std::cout << "collides b1_to_b0?: " << bs1.collides(bs0, v2) << std::endl;
    std::cout << "v2.x: " << v2.x << " v2.y: " << v2.y << std::endl << std::endl;

    return 0;

}
