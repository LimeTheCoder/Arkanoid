#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

const float BALL_VELOCITY = 5.f;

class Ball : public sf::Drawable {
public:
	Ball(float start_x, float start_y);
	void update();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f &pos);

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f &v);

	void setVelocityX(float vx);
	void setVelocityY(float vy);

	float getLeft();
	float getRight();
	float getTop();
	float getBottom();

private:
	sf::CircleShape shape;
	const float radius;
	sf::Vector2f velocity;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif