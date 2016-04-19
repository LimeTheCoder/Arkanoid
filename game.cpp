#include "game.h"
#include "play_state.h"
#include "menu_state.h"

const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const sf::String TITLE = "Arkanoid";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

const int HIGHSCORES_CNT = 8;


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

ResourseManager& Game::getResourseManager() {
    return resourse_manager;
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


void Game::loadHighScores(std::vector<ScoreRecord> &scores) const {
    std::ifstream datafile (ResourceLocations::Highscores);
    if (!datafile.is_open())
        std::cout << "Error to open: " + ResourceLocations::HighscoresData;

    ScoreRecord record;

    while(datafile >> record.name >> record.scores)
        scores.push_back(record);

    datafile.close();
}

void Game::saveScore(ScoreRecord &record) {
    std::vector<ScoreRecord> records;
    loadHighScores(records);

    if(record.scores <= records.back().scores)
        return;

    records.push_back(record);
    std::sort(records.begin(), records.end(),
              [](const ScoreRecord& left, const ScoreRecord& right) {
                  return left.scores > right.scores;});

    std::ofstream scoresfile(ResourceLocations::HighscoresData);
    for(int i = 0; i < HIGHSCORES_CNT; i++)
        scoresfile << (records[i].name + " " + std::to_string(records[i].scores) + " ");

    scoresfile.close();
}