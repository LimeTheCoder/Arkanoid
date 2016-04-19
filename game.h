#ifndef GAME_H
#define GAME_H

#include "resourse_manager.h"
#include <stack>
#include <iostream>
#include <fstream>

extern const unsigned WINDOW_WIDTH;
extern const unsigned WINDOW_HEIGHT;
extern const sf::String TITLE;
extern const sf::Time TIME_PER_FRAME;

extern const int HIGHSCORES_CNT;

class GameState;


namespace States {
    enum Code {
        Menu,
        Game,
        Scores,
        Pause
    };
}


struct ScoreRecord {
    std::string name;
    unsigned scores;
};


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

    void loadHighScores(std::vector<ScoreRecord> &scores) const;
    void saveScore(ScoreRecord &record);

private:
    sf::RenderWindow window;
    const sf::Time time_per_frame;

    std::stack<GameState*> screens;
    ResourseManager resourse_manager;
    ScoreRecord player_score;
};


#endif
