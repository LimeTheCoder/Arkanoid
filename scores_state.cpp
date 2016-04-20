#include "scores_state.h"


const size_t TITLE_SIZE = 80;
const float TITLE_POSITION_X = 300.f;
const float TITLE_POSITION_Y = 7.f;
const size_t SUBTITLE_SIZE = 50;
const size_t BODY_TEXT_SIZE = 45;
const float PLAYER_SUBTITLE_POS_X = 100.f;
const float PLAYER_SUBTITLE_POS_Y = 100.f;
const float MARGIN_TOP = 50.f;
const float MARGIN_LEFT = 550.f;


namespace ScoreStateNames {
    const std::string Title = "HIGHSCORES";
    const std::string Player = "PLAYER";
    const std::string Score = "POINTS";
    const std::string BackToMain = "Press space for back to main menu";
}


ScoresState::ScoresState(Game *state_holder) : GameState(state_holder) {
    sf::Texture *texture = game->getResourseManager().getTexture(Textures::Code::ScoreBackground);
    sf::Font *font = game->getResourseManager().getFont(Fonts::Code::Score);

    backgroundSprite.setTexture(*texture);

    title.setFont(*font);
    title.setString(ScoreStateNames::Title);
    title.setColor(sf::Color::Magenta);
    title.setCharacterSize(TITLE_SIZE);
    title.setPosition(sf::Vector2f(TITLE_POSITION_X,
                                   TITLE_POSITION_Y));

    player_title.setFont(*font);
    player_title.setString(ScoreStateNames::Player);
    player_title.setColor(sf::Color::Cyan);
    player_title.setCharacterSize(SUBTITLE_SIZE);
    player_title.setPosition(sf::Vector2f(PLAYER_SUBTITLE_POS_X,
                                          PLAYER_SUBTITLE_POS_Y));

    scores_title.setFont(*font);
    scores_title.setString(ScoreStateNames::Score);
    scores_title.setColor(sf::Color::Cyan);
    scores_title.setCharacterSize(SUBTITLE_SIZE);
    scores_title.setPosition(sf::Vector2f(PLAYER_SUBTITLE_POS_X + MARGIN_LEFT,
                                          PLAYER_SUBTITLE_POS_Y));

    std::vector<ScoreRecord> vec;
    game->loadHighScores(vec);

    sf::Text player;
    sf::Text score;

    for(int i = 0; i < vec.size(); i++) {
        player.setString(vec[i].name);
        player.setCharacterSize(BODY_TEXT_SIZE);
        player.setFont(*font);
        player.setColor(sf::Color::Blue);
        player.setPosition(sf::Vector2f(PLAYER_SUBTITLE_POS_X,
                                        PLAYER_SUBTITLE_POS_Y + MARGIN_TOP * (i + 1)));

        score.setFont(*font);
        score.setString(std::to_string(vec[i].scores));
        score.setColor(sf::Color::Blue);
        score.setCharacterSize(BODY_TEXT_SIZE);
        score.setPosition(sf::Vector2f(PLAYER_SUBTITLE_POS_X + MARGIN_LEFT + MARGIN_TOP / 2.f,
                                       PLAYER_SUBTITLE_POS_Y + MARGIN_TOP * (i + 1)));

        highscores.push_back(std::make_pair(player, score));
    }

    back_to_main.setFont(*font);
    back_to_main.setString(ScoreStateNames::BackToMain);
    back_to_main.setColor(sf::Color::Cyan);
    back_to_main.setCharacterSize(BODY_TEXT_SIZE);
    back_to_main.setPosition(sf::Vector2f(TITLE_POSITION_X - 120.f,
                                          highscores.back().first.getPosition().y + MARGIN_TOP));
}


/** Nothing to do in update, cause we must update text only in case
 * when user provide input.
 * Not on every loop iteration **/

void ScoresState::update() { }


void ScoresState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backgroundSprite);

    game->getWindow()->draw(title);
    game->getWindow()->draw(player_title);
    game->getWindow()->draw(scores_title);

    game->getWindow()->draw(back_to_main);

    for (const std::pair<sf::Text, sf::Text> &record : highscores) {
        game->getWindow()->draw(record.first);
        game->getWindow()->draw(record.second);
    }

    game->getWindow()->display();
}

void ScoresState::processEvents() {
    sf::Event event;

    while (game->getWindow()->pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::Closed:
                game->popState();
                return;

            case sf::Event::KeyPressed:

                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        game->popState();
                        return;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}