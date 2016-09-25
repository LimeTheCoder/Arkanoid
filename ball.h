#ifndef BALL_H
#define BALL_H

#include "game_object.h"
#include <list>

class Ball;

class IObserver {
public:
	virtual void handleBallPosChange(Ball &ball) = 0;
};

class IObservalble {
public:
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
};

class Ball : public MovableObject, public IObservalble {
public:
	Ball(float start_x, float start_y, float radius, float ball_velocity);
    ~Ball();

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;

    float getRadius() const;
    void setRadius(float radius);

    void attach(IObserver *observer);
    void detach(IObserver *observer);

    void update();

private:
    std::list<IObserver*> observers;
    void notifyObservers();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif