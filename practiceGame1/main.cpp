#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"

void update(const sf::RenderWindow &window, sf::Time tslu, Ball &b) {

    b.update(window, tslu);

}

int main() {

    sf::RenderWindow window(sf::VideoMode(650, 650), "Simple Pong game", sf::Style::Close | sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2.0f - window.getSize().x/2.0f, sf::VideoMode::getDesktopMode().height / 2.0f - window.getSize().y/2.0f));
    window.setFramerateLimit(60);

    float ballR = 10.0f;
    Ball ball(ballR, sf::Color(255, 255, 255, 255), sf::Vector2f((window.getSize().x / 2.0f) - ballR, (window.getSize().y / 2.0f) - ballR), sf::Vector2f(500.0f, -350.0f));

    sf::Vector2f paddleSize(10.0f, window.getSize().y / 7.0f);
    Paddle paddle1(paddleSize, sf::Color(255, 255, 255, 255), sf::Vector2f(paddleSize.x * 2.0f + 10.0f, window.getSize().y / 2.0f - paddleSize.y / 2.0f));
    sf::Clock gameClock;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();
        update(window, gameClock.restart(), ball);
        window.draw(ball.getDrawable());
        window.draw(paddle1.getDrawable());
        window.display();

    }

    return 0;

}