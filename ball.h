#ifndef BALL_H
#define BALL_H

#include "game_object.h"

class Ball : public MovableObject {
public:
	Ball(float start_x, float start_y, float radius, float ball_velocity);
    ~Ball();

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;

    float getRadius() const;
    void setRadius(float radius);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif