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

    Block* clone();

    static unsigned getScore();
    static void resetScore();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateShapeColor();

    int life_cnt;
    static unsigned score;
};

/** Prototype pattern **/

class BlockSpawner {
public:
    BlockSpawner(float width, float height);
    ~BlockSpawner();

    Block* getBlock(int type) const;

private:
    Block *easyBlock;
    Block *mediumBlock;
    Block *strongBlock;
};

#endif
