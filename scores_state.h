#ifndef SCORES_STATE_H
#define SCORES_STATE_H

#include "game_state.h"

class ScoresState : public GameState {
public:
    ScoresState(Game *state_holder);
    ~ScoresState();

    void render();
    void update();
    void processEvents();

private:
    sf::Sprite backgroundSprite;
};


#endif
