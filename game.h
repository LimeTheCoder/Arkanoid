#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>

extern const unsigned WINDOW_WIDTH;
extern const unsigned WINDOW_HEIGHT;
extern const sf::String TITLE;
extern const sf::Time TIME_PER_FRAME;

class GameState;

class Game {
public:
    Game();
    ~Game();

    void run();

    void addState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* getState() const;
    sf::RenderWindow *getWindow();

private:
    sf::RenderWindow window;
    const sf::Time time_per_frame;

    std::stack<GameState*> screens;
};


#endif
