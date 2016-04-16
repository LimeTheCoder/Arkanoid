#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable {
public:

    GameObject(sf::Vector2f coords, sf::Shape *shape,
               sf::Vector2f velocity, const sf::Color &color);

    void update();

    sf::Vector2f getPosition();
    void setPosition(const sf::Vector2f &pos);

    sf::Vector2f getVelocity();
    void setVelocity(const sf::Vector2f &v);

    void setVelocityX(float vx);
    void setVelocityY(float vy);

    virtual float getLeft() = 0;
    virtual float getRight() = 0;
    virtual float getTop() = 0;
    virtual float getBottom() = 0;

protected:
    sf::Shape *shape;
    sf::Vector2f velocity;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


#endif
