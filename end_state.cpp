#include "end_state.h"

namespace EndStateConstants {
    const size_t GAME_OVER_TITLE_SIZE = 80;

    const float GAME_OVER_TITLE_POSITION_X = 300.f;
    const float GAME_OVER_TITLE_POSITION_Y = 50.f;

    const size_t TITLE_SIZE = 70;
    const float TITLE_POSITION_X = 200.f;
    const float TITLE_POSITION_Y = 200.f;
    const size_t SUBTITLE_SIZE = 50;
    const float SUBTITLE_POS_X = 100.f;
    const float SUBTITLE_POS_Y = 400.f;
    const float MARGIN_TOP = 80.f;
}


namespace EndStateNames {
    const std::string GameResults = "You've reached ";
    const std::string BackToMainMenu = "Press esc to go back to main menu";
    const std::string PlayAgain = "Press space to play again";
}


EndState::EndState(Game *state_holder) :
        GameState(state_holder)
{
    sf::Texture *texture = game->getResourseManager().getTexture(Textures::Code::GameBackground);
    sf::Font *font = game->getResourseManager().getFont(Fonts::Code::Menu);

    backgroundSprite.setTexture(*texture);

    std::string result = EndStateNames::GameResults +
            std::to_string(game->getPlayerScore()) + " points!";

    if(game->isWin())
        game_over.setString("YOU WINNER");
    else
        game_over.setString("GAME OVER");

    game_over.setFont(*font);
    game_over.setColor(sf::Color::Yellow);
    game_over.setCharacterSize(EndStateConstants::GAME_OVER_TITLE_SIZE);
    game_over.setPosition(sf::Vector2f(EndStateConstants::GAME_OVER_TITLE_POSITION_X,
                                       EndStateConstants::GAME_OVER_TITLE_POSITION_Y));

    game_results.setFont(*font);
    game_results.setString(result);
    game_results.setColor(sf::Color::Yellow);
    game_results.setCharacterSize(EndStateConstants::TITLE_SIZE);
    game_results.setPosition(sf::Vector2f(EndStateConstants::TITLE_POSITION_X,
                                          EndStateConstants::TITLE_POSITION_Y));

    back_to_main.setFont(*font);
    back_to_main.setString(EndStateNames::BackToMainMenu);
    back_to_main.setColor(sf::Color::Magenta);
    back_to_main.setCharacterSize(EndStateConstants::SUBTITLE_SIZE);
    back_to_main.setPosition(sf::Vector2f(EndStateConstants::SUBTITLE_POS_X,
                                          EndStateConstants::SUBTITLE_POS_Y));

    play_again.setFont(*font);
    play_again.setString(EndStateNames::PlayAgain);
    play_again.setColor(sf::Color::Magenta);
    play_again.setCharacterSize(EndStateConstants::SUBTITLE_SIZE);
    play_again.setPosition(sf::Vector2f(EndStateConstants::SUBTITLE_POS_X,
                                        EndStateConstants::SUBTITLE_POS_Y + EndStateConstants::MARGIN_TOP));
}

/** Nothing to do in update, cause we must update text only in case
 * when user provide input.
 * Not on every loop iteration **/

void EndState::update() { }


void EndState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backgroundSprite);

    game->getWindow()->draw(game_over);
    game->getWindow()->draw(game_results);
    game->getWindow()->draw(back_to_main);

    game->getWindow()->draw(play_again);

    game->getWindow()->display();
}

void EndState::processEvents() {
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
                        game->changeState(States::Game);
                        return;
                    case sf::Keyboard::Escape:
                        game->changeState(States::Menu);
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