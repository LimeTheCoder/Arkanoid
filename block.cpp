#include "block.h"

Block::Block(float start_x, float start_y, float width, float height, int durability) :
        GameObject(sf::Vector2f(start_x, start_y),
                                 new sf::RectangleShape(), sf::Color(100, 0, 0)),
        life_cnt(durability) {

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

void Block::onHint() {
    life_cnt--;

}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::RectangleShape*>(shape), states);
}