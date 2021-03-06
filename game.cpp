#include "game.h"
#include "play_state.h"
#include "menu_state.h"
#include "scores_state.h"
#include "end_state.h"

const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const sf::String TITLE = "Arkanoid";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

const int HIGHSCORES_CNT = 8;


Game::Game() :
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
        time_per_frame(TIME_PER_FRAME),
        isPaused(false),
        isWinner(false)
{
    addState(States::Code::Menu);
    player_score.scores = 0;
    player_score.name = "You";
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
            screens.push(new ScoresState(this));
            break;
        case States::Code::EndGame:
            screens.push(new EndState(this));
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


void Game::changePauseState() {
    isPaused = !isPaused;
}

bool Game::getPauseState() const {
    return isPaused;
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        if(getState() == nullptr)
            return;

        while(timeSinceLastUpdate > time_per_frame) {
            if(!isPaused)
                getState()->update();
            timeSinceLastUpdate -= time_per_frame;
        }

        getState()->render();
        getState()->processEvents();
    }
}


void Game::loadHighScores(std::vector<ScoreRecord> &scores) const {
    std::ifstream datafile (ResourceLocations::HighscoresData);
    if (!datafile.is_open())
        std::cout << "Error to open: " + ResourceLocations::HighscoresData;

    ScoreRecord record;

    while(datafile >> record.name >> record.scores)
        scores.push_back(record);

    datafile.close();
}

void Game::saveScore() {
    std::vector<ScoreRecord> records;
    loadHighScores(records);

    if(player_score.scores <= records.back().scores)
        return;

    records.push_back(player_score);
    std::sort(records.begin(), records.end(),
              [](const ScoreRecord& left, const ScoreRecord& right) {
                  return left.scores > right.scores;});

    std::ofstream scoresfile(ResourceLocations::HighscoresData);
    for(int i = 0; i < HIGHSCORES_CNT; i++)
        scoresfile << (records[i].name + " " + std::to_string(records[i].scores) + " ");

    scoresfile.close();
}

void Game::setGameScore(unsigned score) {
    player_score.scores = score;
}

unsigned Game::getPlayerScore() const {
    return player_score.scores;
}

std::string Game::getPlayerName() const {
    return player_score.name;
}

void Game::setWinnerStatus(bool is_win) {
    isWinner = is_win;
}

bool Game::isWin() const {
    return isWinner;
}