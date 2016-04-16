#include "paddle.h"

Paddle::Paddle(float start_x, float start_y, float width, float height,
               float paddle_velocity) :
        GameObject(sf::Vector2f(start_x, start_y), new sf::RectangleShape(),
                   sf::Vector2f(paddle_velocity, paddle_velocity), sf::Color::Magenta)
{

    setSize(sf::Vector2f(width, height));
    dynamic_cast<sf::RectangleShape*>(shape)->setOrigin(width / 2.f, height / 2.f);
}

Paddle::~Paddle() {
    if(shape != nullptr)
        delete dynamic_cast<sf::RectangleShape*>(shape);
}

float Paddle::getWidth() {
    return dynamic_cast<sf::RectangleShape*>(shape)->getSize().x;
}

float Paddle::getHeight() {
    return dynamic_cast<sf::RectangleShape*>(shape)->getSize().y;
}

void Paddle::setSize(const sf::Vector2f &size) {
    dynamic_cast<sf::RectangleShape*>(shape)->setSize(size);
}

float Paddle::getRight() {
    return getPosition().x + getWidth() / 2.f;
}

float Paddle::getLeft() {
    return getPosition().x - getWidth() / 2.f;
}

float Paddle::getTop() {
    return getPosition().y - getHeight() / 2.f;
}

float Paddle::getBottom() {
    return getPosition().y + getHeight() / 2.f;
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::RectangleShape*>(shape), states);
}
