#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "game_state.h"


class MenuState : public GameState {
public:
    MenuState(Game *state_holder);
    ~MenuState();

    void render();
    void update();
    void processEvents();

private:
    enum Option {
        Play,
        Scores,
        Exit
    };

    std::size_t selected;
    sf::Sprite backgroundSprite;

    std::vector<sf::Text> options;

    void updateOptions();
};


#endif
