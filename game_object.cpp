#include "game_object.h"

/** Game object implementation part **/

GameObject::GameObject(sf::Vector2f coords, sf::Shape *form,
                       const sf::Color &color) {
    shape = form;
    shape->setPosition(coords);
    shape->setFillColor(color);
}

sf::Vector2f GameObject::getPosition() const {
    return shape->getPosition();
}

void GameObject::setPosition(const sf::Vector2f &pos) {
    shape->setPosition(pos);
}

bool GameObject::isIntersects(const GameObject& another) const {
    return this->getRight() >= another.getLeft() && this->getLeft() <= another.getRight() &&
           this->getBottom() >= another.getTop() && this->getTop() <= another.getBottom();
}


/** Movable object implementation part **/


MovableObject::MovableObject(sf::Vector2f coords, sf::Shape *form,
        sf::Vector2f vel, const sf::Color &color) :
        GameObject(coords, form, color), velocity(vel) { }

void MovableObject::update() {
    shape->move(velocity);
}

sf::Vector2f MovableObject::getVelocity() const {
    return velocity;
}

void MovableObject::setVelocity(const sf::Vector2f &v) {
    velocity = v;
}

void MovableObject::setVelocityX(float vx) {
    velocity.x = vx;
}

void MovableObject::setVelocityY(float vy) {
    velocity.y = vy;
}