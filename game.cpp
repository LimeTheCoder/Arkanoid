#include "game.h"
#include "play_state.h"
#include "menu_state.h"

const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const sf::String TITLE = "Arkanoid";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);


Game::Game() :
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
        time_per_frame(TIME_PER_FRAME) {
    addState(States::Code::Menu);
}

Game::~Game() {
    while(!screens.empty()) popState();
}


GameState* Game::getState() const {
    if(screens.empty()) return nullptr;
    return screens.top();
}

void Game::addState(States::Code state) {
    switch (state) {
        case States::Code::Game:
            screens.push(new PlayState(this));
            break;
        case States::Code::Menu:
            screens.push(new MenuState(this));
            break;
        case States::Code::Pause:
            break;
        case States::Code::Scores:
            break;
        default:
            break;
    }
}

void Game::changeState(States::Code state) {
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


        while(timeSinceLastUpdate > time_per_frame) {
            getState()->update();
            timeSinceLastUpdate -= time_per_frame;
        }

        getState()->render();
        getState()->processEvents();
    }
}