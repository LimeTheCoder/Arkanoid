#include "menu_state.h"

MenuState::MenuState(Game *state_holder) :
        GameState(state_holder), selected(0) {
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("Media/images/menu_background.jpg");

    sf::Font *font = new sf::Font();

    font->loadFromFile("Media/fonts/option_font.otf");
    backgroundSprite.setTexture(*texture);

    sf::Text playOption;
    playOption.setFont(*font);
    playOption.setString("Play");
    playOption.setCharacterSize(70);
    playOption.setPosition(sf::Vector2f(350.f, 150.f));
    options.push_back(playOption);


    sf::Text scoresOption;
    scoresOption.setFont(*font);
    scoresOption.setString("Scores");
    scoresOption.setCharacterSize(70);
    scoresOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 70.f));
    options.push_back(scoresOption);

    sf::Text exitOption;
    exitOption.setFont(*font);
    exitOption.setCharacterSize(70);
    exitOption.setString("Exit");
    exitOption.setPosition(scoresOption.getPosition() + sf::Vector2f(0.f, 70.f));
    options.push_back(exitOption);

    updateOptions();
}

MenuState::~MenuState() {
    delete options[0].getFont();
    delete backgroundSprite.getTexture();
}

void MenuState::updateOptions() {
    for(sf::Text &option : options)
        option.setColor(sf::Color::White);

    options[selected].setColor(sf::Color::Blue);
}

/** Nothing to do in update, cause we must update text in case
 * when user provide input.
 * Not on every loop iteration **/

void MenuState::update() { }


void MenuState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backgroundSprite);

    for(sf::Text &option : options) {
        game->getWindow()->draw(option);
    }

    game->getWindow()->display();
}

void MenuState::processEvents() {
    sf::Event event;

    while (game->getWindow()->pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::Closed:
                game->popState();
                return;

            case sf::Event::KeyPressed:

                switch (event.key.code)
                {

                    case sf::Keyboard::Up:
                        selected = selected > 0 ? selected - 1 :
                                   options.size() - 1;
                        updateOptions();
                        break;

                    case sf::Keyboard::Down:
                        selected = (selected + 1) % options.size();
                        updateOptions();
                        break;

                    case sf::Keyboard::Return:
                        switch (selected)
                        {
                            case Play:
                                game->changeState(States::Game);
                                return;
                            case Scores:
                                break;
                            case Exit:
                                game->popState();
                                return;
                            default:
                                break;
                        }

                    default:
                        break;
                }

                break;

            default:
                break;
        }
    }
}