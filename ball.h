#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
public:
	Ball(float start_x, float start_y);
	void update();

private:
	sf::CircleShape shape;
	const float radius;
	const float default_velocity;
	sf::Vector2f velocity;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(shape, states);
	}
};


#endif