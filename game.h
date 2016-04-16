#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "paddle.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const sf::String TITLE;
extern const sf::Time TIME_PER_FRAME;

extern const float BALL_VELOCITY;
extern const float BALL_RADIUS;
extern const float BALL_START_COORD_X;
extern const float BALL_START_COORD_Y;

extern const float PADDLE_VELOCITY;
extern const float PADDLE_WIDTH;
extern const float PADDLE_HEIGHT;
extern const float PADDLE_START_COORD_X;
extern const float PADDLE_START_COORD_Y;

class AbstractGame {
public:
    AbstractGame(unsigned int window_width, unsigned int window_height,
                 sf::String title, sf::Time time_per_frame);
    void run();

protected:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void processEvents() = 0;

	sf::RenderWindow window;
	const sf::Time TimePerFrame;
};


class Game : public AbstractGame {
public:
	Game();

	void render();
	void update();
	void processEvents();

private:
	Ball ball;
    Paddle paddle;
};

#endif
