#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable {
public:

    GameObject(sf::Vector2f coords, sf::Shape *shape, const sf::Color &color);

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &pos);

    virtual float getLeft() const = 0;
    virtual float getRight() const = 0;
    virtual float getTop() const = 0;
    virtual float getBottom() const = 0;

    bool isIntersects(const GameObject& another) const;

protected:
    sf::Shape *shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


class MovableObject : public GameObject {
public:

    MovableObject(sf::Vector2f coords, sf::Shape *shape, float speed_rate,
               sf::Vector2f velocity, const sf::Color &color);

    virtual void update();

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f &v);

    void setVelocityX(float vx);
    void setVelocityY(float vy);

    float getMoveRate() const;
protected:
    sf::Vector2f velocity;
    float move_rate;
};


#endif
