#ifndef PADDLE_H
#define PADDLE_H

#include "game_object.h"


class Paddle : public GameObject {
public:
    Paddle(float start_x, float start_y, float width, float height,
                   float paddle_velocity);

    ~Paddle();

    float getWidth();
    float getHeight();

    float getLeft();
    float getRight();
    float getTop();
    float getBottom();

    void setSize(const sf::Vector2f &size);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
