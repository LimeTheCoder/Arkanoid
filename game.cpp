#include "game.h"
#include "play_state.h"

const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const sf::String TITLE = "Arkanoid";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);


Game::Game() :
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
        time_per_frame(TIME_PER_FRAME) {
    addState(new PlayState(this));
}

Game::~Game() {
    while(!screens.empty()) popState();
}


GameState* Game::getState() const {
    if(screens.empty()) return nullptr;
    return screens.top();
}

void Game::addState(GameState* state) {
    screens.push(state);
}

void Game::changeState(GameState* state) {
    if(!screens.empty())
        popState();
    addState(state);
}

void Game::popState() {
    delete screens.top();
    screens.pop();
}


sf::RenderWindow *Game::getWindow() {
    return &window;
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        if(getState() == nullptr)
            return;

        getState()->processEvents();

        while(timeSinceLastUpdate > time_per_frame) {
            getState()->update();
            timeSinceLastUpdate -= time_per_frame;
        }

        getState()->render();
    }
}