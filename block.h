#ifndef BLOCK_H
#define BLOCK_H

#include "ball.h"

class Block : public GameObject {
public:
    Block(float start_x, float start_y, float width, float height, int durability);
    ~Block();

    float getWidth() const;
    float getHeight() const;

    void setSize(const sf::Vector2f &size);

    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;

    bool isAlive() const;
    void onHint();

    void handleBallCollision(Ball &ball);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int life_cnt;
};


#endif
