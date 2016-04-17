#ifndef PADDLE_H
#define PADDLE_H

#include "game_object.h"


class Paddle : public MovableObject {
public:
    Paddle(float start_x, float start_y, float width, float height, float speed);
    ~Paddle();

    float getWidth() const;
    float getHeight() const;

    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;

    void moveLeft();
    void moveRight();
    void stayAtPlace();

    void setSize(const sf::Vector2f &size);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float move_rate;
};

#endif
