#include "ball.h"

Ball::Ball(float start_x, float start_y) : radius(10.f),
	velocity(-BALL_VELOCITY, -BALL_VELOCITY)
{
	shape.setPosition(800 - start_x, 600 - start_y);
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(radius, radius);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
}

void Ball::update() { 
	shape.move(velocity);
}

sf::Vector2f Ball::getPosition() {
    return shape.getPosition();
}

void Ball::setPosition(sf::Vector2f &pos) {
    shape.setPosition(pos);
}


sf::Vector2f Ball::getVelocity() {
    return velocity;
}

void Ball::setVelocity(sf::Vector2f &v) {
    velocity = v;
}

void Ball::setVelocityX(float vx) {
    velocity.x = vx;
}

void Ball::setVelocityY(float vy) {
    velocity.y = vy;
}

float Ball::getLeft() {
    return getPosition().x - shape.getRadius();
}

float Ball::getRight() {
    return getPosition().x + shape.getRadius();
}

float Ball::getTop() {
    return getPosition().y - shape.getRadius();
}

float Ball::getBottom() {
    return getPosition().y + shape.getRadius();
}