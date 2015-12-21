#include<iostream>
#include"../../src/elements/Entity.hpp"

int main() {

    sg::Entity e = sg::Entity(sf::Vector2f(10.0f, 100.0f));
    std::cout << e.getPos().x << std::endl;
    std::cout << e.getPos().y << std::endl;
    std::cout << e.getIsCollidable() << std::endl;

    return 0;

}
