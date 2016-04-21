#ifndef END_STATE_H
#define END_STATE_H

#include "game_state.h"


namespace EndStateConstants {
    extern const size_t GAME_OVER_TITLE_SIZE;

    extern const float GAME_OVER_TITLE_POSITION_X;
    extern const float GAME_OVER_TITLE_POSITION_Y;


    extern const size_t TITLE_SIZE;
    extern const size_t SUBTITLE_SIZE;

    extern const float TITLE_POSITION_X;
    extern const float TITLE_POSITION_Y;
    extern const float SUBTITLE_POS_X;
    extern const float SUBTITLE_POS_Y;

    extern const float MARGIN_TOP;
}


namespace EndStateNames {
    extern const std::string GameResults;
    extern const std::string GameOverTitle;
    extern const std::string BackToMainMenu;
    extern const std::string PlayAgain;
}


class EndState : public GameState {
public:
    EndState(Game *state_holder);

    void render();
    void update();
    void processEvents();

private:
    sf::Sprite backgroundSprite;
    sf::Text game_results;
    sf::Text game_over;
    sf::Text back_to_main;
    sf::Text play_again;
};


#endif
