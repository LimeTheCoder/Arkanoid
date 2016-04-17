#include "block.h"

Block::Block(float start_x, float start_y, float width, float height, int durability) :
        GameObject(sf::Vector2f(start_x, start_y),
                                 new sf::RectangleShape(), sf::Color::Yellow)
{
    life_cnt = (durability <= 3 && durability > 0) ? durability : 3;
    updateShapeColor();
    setSize(sf::Vector2f(width, height));
    dynamic_cast<sf::RectangleShape*>(shape)->setOrigin(width / 2.f, height / 2.f);
}

Block::~Block() {
    if(shape != nullptr)
        delete dynamic_cast<sf::RectangleShape*>(shape);
    shape = nullptr;
}

void Block::setSize(const sf::Vector2f &size) {
    dynamic_cast<sf::RectangleShape*>(shape)->setSize(size);
}

float Block::getWidth() const {
    return dynamic_cast<sf::RectangleShape*>(shape)->getSize().x;
}

float Block::getHeight() const {
    return dynamic_cast<sf::RectangleShape*>(shape)->getSize().y;
}

float Block::getRight() const {
    return getPosition().x + getWidth() / 2.f;
}

float Block::getLeft() const {
    return getPosition().x - getWidth() / 2.f;
}

float Block::getTop() const {
    return getPosition().y - getHeight() / 2.f;
}

float Block::getBottom() const {
    return getPosition().y + getHeight() / 2.f;
}

bool Block::isAlive() const {
    return life_cnt != 0;
}

void Block::updateShapeColor() {
    switch (life_cnt) {
        case 3:
            shape->setFillColor(sf::Color(90, 0, 0));
            break;
        case 2:
            shape->setFillColor(sf::Color(160, 85, 0));
            break;
        case 1:
            shape->setFillColor(sf::Color::Yellow);
            break;
        default:
            break;
    }
}

void Block::onHint() {
    life_cnt--;
    updateShapeColor();
}

void Block::handleBallCollision(Ball &ball) {
    if(!isIntersects(ball)) return;

    onHint();

    float overlapLeft = ball.getRight() - getLeft();
    float overlapRight = getRight() - ball.getLeft();
    float overlapTop= ball.getBottom() - getTop();
    float overlapBottom = getBottom() - ball.getTop();

    bool ballFromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
    bool ballFromTop = std::abs(overlapTop) < std::abs(overlapBottom);

    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

    if(std::abs(minOverlapX) < std::abs(minOverlapY))
        ball.setVelocityX(ballFromLeft ? -ball.getMoveRate() : ball.getMoveRate());
    else
        ball.setVelocityY(ballFromTop ? -ball.getMoveRate() : ball.getMoveRate());
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::RectangleShape*>(shape), states);
}

Block* Block::clone() {
    return new Block(getPosition().x, getPosition().y, getWidth(), getHeight(), life_cnt);
}

/** Prototype pattern implementation **/

BlockSpawner::BlockSpawner(float width, float height) {
    easyBlock = new Block(0.f, 0.f, width, height, 1);
    mediumBlock = new Block(0.f, 0.f, width, height, 2);
    strongBlock = new Block(0.f, 0.f, width, height, 3);
}

BlockSpawner::~BlockSpawner() {
    delete easyBlock;
    delete mediumBlock;
    delete strongBlock;
}

Block* BlockSpawner::getBlock(int type) const {
    Block *out = nullptr;

    switch (type) {
        case 3:
            out = strongBlock->clone();
            break;
        case 2:
            out = mediumBlock->clone();
            break;
        case 1:
            out = easyBlock->clone();
            break;
        default:
            break;
    }

    return out;
}