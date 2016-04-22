#include "ball.h"


Ball::Ball(float start_x, float start_y, float radius, float ball_velocity) :
        MovableObject(sf::Vector2f(start_x, start_y), new sf::CircleShape(), ball_velocity,
                     sf::Vector2f(ball_velocity, ball_velocity), sf::Color::Red)
{
    shape->setOrigin(radius, radius);
    setRadius(radius);
}

Ball::~Ball() {
    if(shape != nullptr)
        delete dynamic_cast<sf::CircleShape*>(shape);
    shape = nullptr;
}

float Ball::getRadius() const {
    return dynamic_cast<sf::CircleShape*>(shape)->getRadius();
}

void Ball::setRadius(float radius) {
    dynamic_cast<sf::CircleShape*>(shape)->setRadius(radius);
}

float Ball::getLeft() const {
    return getPosition().x - getRadius();
}

float Ball::getRight() const {
    return getPosition().x + getRadius();
}

float Ball::getTop() const {
    return getPosition().y - getRadius();
}

float Ball::getBottom() const {
    return getPosition().y + getRadius();
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::CircleShape*>(shape), states);
}


/** Observer pattern implementation part **/
void Ball::attach(IObserver *observer) {
    observers.push_back(observer);
}

void Ball::detach(IObserver *observer) {
    observers.remove(observer);
}

void Ball::notifyObservers() {
    for(IObserver *iter : observers) {
        iter->handleBallPosChange(*this);
    }
}

void Ball::update() {
    MovableObject::update();
    notifyObservers();
}