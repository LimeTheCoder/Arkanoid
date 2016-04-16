#include "ball.h"

Ball::Ball(float start_x, float start_y) : radius(10.f), default_velocity(4.f),
	velocity(-default_velocity, -default_velocity)  
{
	shape.setPosition(800 - start_x, 600 - start_y);
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(radius, radius);
}

void Ball::update() { 
	shape.move(velocity); 
}