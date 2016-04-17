#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "paddle.h"
#include "command.h"
#include "block.h"
#include "game_state.h"


extern const float BALL_VELOCITY;
extern const float BALL_RADIUS;
extern const float BALL_START_COORD_X;
extern const float BALL_START_COORD_Y;

extern const float PADDLE_VELOCITY;
extern const float PADDLE_WIDTH;
extern const float PADDLE_HEIGHT;
extern const float PADDLE_START_COORD_X;
extern const float PADDLE_START_COORD_Y;

extern const float BLOCK_WIDTH;
extern const float BLOCK_HEIGHT;
extern const int BLOCK_ROWS_CNT;
extern const int BLOCK_COLUMNS_CNT;

extern const sf::Keyboard::Key BUTTON_LEFT;
extern const sf::Keyboard::Key BUTTON_RIGHT;


class PlayState : public GameState {
public:
    PlayState(Game *state_holder);
    ~PlayState();

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

   std::vector<Block*> blocks;

};

#endif
