#include "play_state.h"


const float PADDLE_VELOCITY = 6.f;
const float PADDLE_WIDTH = 60.f;
const float PADDLE_HEIGHT = 15.f;
const float PADDLE_START_COORD_X = WINDOW_WIDTH / 2.f;
const float PADDLE_START_COORD_Y = WINDOW_HEIGHT - 30.f;

const float BALL_VELOCITY = 5.f;
const float BALL_RADIUS = 9.f;
const float BALL_START_COORD_X = PADDLE_START_COORD_X;
const float BALL_START_COORD_Y = PADDLE_START_COORD_Y + BALL_RADIUS;

const float BLOCK_WIDTH = 50.f;
const float BLOCK_HEIGHT = 20.f;
const int BLOCK_ROWS_CNT = 4;
const int BLOCK_COLUMNS_CNT = 11;

const sf::Keyboard::Key BUTTON_LEFT = sf::Keyboard::Key::Left;
const sf::Keyboard::Key BUTTON_RIGHT = sf::Keyboard::Key::Right;


PlayState::PlayState(Game *state_holder) :
        GameState(state_holder),
        ball(BALL_START_COORD_X, BALL_START_COORD_Y, BALL_RADIUS, BALL_VELOCITY),
        paddle(PADDLE_START_COORD_X, PADDLE_START_COORD_Y,
               PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_VELOCITY),
        isGameOver(false)
{
    Block::resetScore();

    default_command = new DefaultCommand();
    button_left = new MoveLeftCommand();
    button_right = new MoveRightCommand();
    current_command = default_command;


    sf::Texture *texture = game->getResourseManager().getTexture(Textures::Code::GameBackground);
    backgroundSprite.setTexture(*texture);

    BlockSpawner spawner(BLOCK_WIDTH, BLOCK_HEIGHT);
    Block *curr = nullptr;

    ball.attach(&paddle);

    for(int i = 0; i < BLOCK_COLUMNS_CNT; i++)
        for(int j = 0; j < BLOCK_ROWS_CNT; j++) {
            curr = spawner.getBlock(j % 3 + 1);
            curr->setPosition(sf::Vector2f((i + 1) * (BLOCK_WIDTH + 2) + 75,
                                           (j + 1) * (BLOCK_HEIGHT + 2) + 50));
            blocks.push_back(curr);
            ball.attach(curr);
        }

    sf::Font *font = game->getResourseManager().getFont(Fonts::Score);

    score_text.setColor(sf::Color::Cyan);
    score_text.setCharacterSize(40);
    score_text.setPosition(WINDOW_WIDTH - 150.f, 0.f);
    score_text.setFont(*font);


    pause_text.setColor(sf::Color(255, 255, 255));
    pause_text.setCharacterSize(65);
    pause_text.setPosition(WINDOW_WIDTH / 2.f - 50.f, WINDOW_HEIGHT / 2.f - 50.f);
    pause_text.setFont(*font);
    pause_text.setString("PAUSED");
}

PlayState::~PlayState() {
    if(button_left != nullptr)
        delete button_left;

    if(button_right != nullptr)
        delete button_right;

    if(default_command != nullptr)
        delete default_command;

    for (Block *block : blocks) {
        delete block;
    }

    blocks.clear();
}


void PlayState::processEvents() {
	sf::Event event;

    if(isGameOver) {
        game->setGameScore(Block::getScore());
        game->saveScore();
        game->changeState(States::EndGame);
        return;
    }

	while (game->getWindow()->pollEvent(event)) {
	    switch (event.type) 
	    {
	        case sf::Event::Closed:
                game->setGameScore(Block::getScore());
                game->popState();
	            return;

            case sf::Event::KeyPressed:

                switch (event.key.code) {
                    case sf::Keyboard::P:
                        game->changePauseState();
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


    if(sf::Keyboard::isKeyPressed(BUTTON_LEFT) && paddle.getLeft() > 0)
        current_command = button_left;
    else if(sf::Keyboard::isKeyPressed(BUTTON_RIGHT) &&
            paddle.getRight() < WINDOW_WIDTH)
        current_command = button_right;
    else
        current_command = default_command;
}


void PlayState::update() {
	if(ball.getLeft() < 0)
		ball.setVelocityX(BALL_VELOCITY);
	else if(ball.getRight() > WINDOW_WIDTH)
		ball.setVelocityX(-BALL_VELOCITY);

	if(ball.getTop() < 0)
		ball.setVelocityY(BALL_VELOCITY);
	else if(ball.getBottom() > WINDOW_HEIGHT) {
        isGameOver = true;
        return;
    }

    if(current_command != nullptr)
        current_command->Execute(paddle);


    if(blocks.size() == 0) {
        game->setWinnerStatus(true);
        isGameOver = true;
        return;
    }

    ball.update();
    paddle.update();

    for(int i = 0; i < blocks.size(); i++) {
        if(!blocks[i]->isAlive()) {
            ball.detach(blocks[i]);
            delete blocks[i];
            blocks.erase(blocks.begin() + i);
            i--;
        }
    }

    sf::String scores_string = sf::String("SCORE: ") +
            sf::String(std::to_string(Block::getScore()));
    score_text.setString(scores_string);
}


void PlayState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backgroundSprite);
    game->getWindow()->draw(ball);
    game->getWindow()->draw(paddle);

    game->getWindow()->draw(score_text);

    for(Block *block : blocks)
        game->getWindow()->draw(*block);

    if(game->getPauseState())
        game->getWindow()->draw(pause_text);

    game->getWindow()->display();
}
