#ifndef GAME_H
#define GAME_H

#include "absract_game.h"
#include "ball.h"
#include "paddle.h"
#include "command.h"

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

extern const sf::Keyboard::Key BUTTON_LEFT;
extern const sf::Keyboard::Key BUTTON_RIGHT;

class Game : public AbstractGame {
public:
	Game();
    ~Game();

	void render();
	void update();
	void processEvents();

private:
	Ball ball;
    Paddle paddle;
    Command *current_command;
    Command *button_left;
    Command *button_right;
    Command *default_command;
};

#endif
