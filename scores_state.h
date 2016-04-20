#ifndef SCORES_STATE_H
#define SCORES_STATE_H

#include "game_state.h"


extern const size_t TITLE_SIZE;
extern const size_t SUBTITLE_SIZE;
extern const size_t BODY_TEXT_SIZE;

extern const float TITLE_POSITION_X;
extern const float TITLE_POSITION_Y;
extern const float PLAYER_SUBTITLE_POS_X;
extern const float PLAYER_SUBTITLE_POS_Y;

extern const float MARGIN_TOP;
extern const float MARGIN_LEFT;

namespace ScoreStateNames {
    extern const std::string Title;
    extern const std::string Player;
    extern const std::string Score;
    extern const std::string BackToMain;
}


class ScoresState : public GameState {
public:
    ScoresState(Game *state_holder);

    void render();
    void update();
    void processEvents();

private:
    sf::Sprite backgroundSprite;

    sf::Text title;
    sf::Text player_title;
    sf::Text scores_title;
    sf::Text back_to_main;

    std::vector<std::pair<sf::Text, sf::Text>> highscores;
};


#endif
