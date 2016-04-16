#include "game_object.h"


GameObject::GameObject(sf::Vector2f coords, sf::Shape *form,
        sf::Vector2f vel, const sf::Color &color) {
    shape = form;
    velocity = vel;
    shape->setPosition(coords);
    shape->setFillColor(color);
}

GameObject::~GameObject() {
    if(shape != nullptr)
        delete shape;
}

void GameObject::update() {
    shape->move(velocity);
}

sf::Vector2f GameObject::getPosition() {
    return shape->getPosition();
}

void GameObject::setPosition(const sf::Vector2f &pos) {
    shape->setPosition(pos);
}

sf::Vector2f GameObject::getVelocity() {
    return velocity;
}

void GameObject::setVelocity(const sf::Vector2f &v) {
    velocity = v;
}

void GameObject::setVelocityX(float vx) {
    velocity.x = vx;
}

void GameObject::setVelocityY(float vy) {
    velocity.y = vy;
}