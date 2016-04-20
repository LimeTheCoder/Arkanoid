#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "game_state.h"

extern const size_t CHARACTER_SIZE;
extern const float MENU_POSITION_X;
extern const float MENU_POSITION_Y;

namespace OptionNames {
    extern const std::string Play;
    extern const std::string Scores;
    extern const std::string Exit;
}


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
