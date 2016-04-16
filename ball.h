#ifndef BALL_H
#define BALL_H

#include "game_object.h"

class Ball : public GameObject {
public:
	Ball(float start_x, float start_y, float radius, float ball_velocity);
    ~Ball();

	float getLeft();
	float getRight();
	float getTop();
	float getBottom();

    float getRadius();
    void setRadius(float radius);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif