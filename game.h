#ifndef GAME_H
#define GAME_H

#include "resourse_manager.h"
#include <stack>

extern const unsigned WINDOW_WIDTH;
extern const unsigned WINDOW_HEIGHT;
extern const sf::String TITLE;
extern const sf::Time TIME_PER_FRAME;

class GameState;


namespace States {
    enum Code {
        Menu,
        Game,
        Scores,
        Pause
    };
}


class Game {
public:
    Game();
    ~Game();

    void run();

    void addState(States::Code state);
    void popState();
    void changeState(States::Code state);
    GameState* getState() const;
    sf::RenderWindow *getWindow();

    ResourseManager& getResourseManager();

private:
    sf::RenderWindow window;
    const sf::Time time_per_frame;

    std::stack<GameState*> screens;
    ResourseManager resourse_manager;
};


#endif
