#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game.h"

class GameState {
public:
    GameState(Game *state_holder) : game(state_holder) {}

    virtual void render() = 0;
    virtual void update() = 0;
    virtual void processEvents() = 0;

protected:
    Game *game;
};

#endif
