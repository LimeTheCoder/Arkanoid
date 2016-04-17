#include "play_state.h"


const float PADDLE_VELOCITY = 6.f;
const float PADDLE_WIDTH = 60.f;
const float PADDLE_HEIGHT = 15.f;
const float PADDLE_START_COORD_X = WINDOW_WIDTH / 2.f;
const float PADDLE_START_COORD_Y = WINDOW_HEIGHT - 30.f;

const float BALL_VELOCITY = 6.f;
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
               PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_VELOCITY)
{
    default_command = new DefaultCommand();
    button_left = new MoveLeftCommand();
    button_right = new MoveRightCommand();
    current_command = default_command;

    BlockSpawner spawner(BLOCK_WIDTH, BLOCK_HEIGHT);
    Block *curr = nullptr;

    for(int i = 0; i < BLOCK_COLUMNS_CNT; i++)
        for(int j = 0; j < BLOCK_ROWS_CNT; j++) {
            curr = spawner.getBlock(j % 3 + 1);
            curr->setPosition(sf::Vector2f((i + 1) * (BLOCK_WIDTH + 2) + 75,
                                           (j + 1) * (BLOCK_HEIGHT + 2) + 50));
            blocks.push_back(curr);
        }
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

	while (game->getWindow()->pollEvent(event)) {
	    switch (event.type) 
	    {
	        case sf::Event::Closed:
                game->getWindow()->close();
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
	else if(ball.getBottom() > WINDOW_HEIGHT)
		ball.setVelocityY(-BALL_VELOCITY);

    if(current_command != nullptr)
        current_command->Execute(paddle);

    paddle.handleBallCollision(ball);

    for(Block* block : blocks) block->handleBallCollision(ball);


    for(int i = 0; i < blocks.size(); i++) {
        if(!blocks[i]->isAlive()) {
            delete blocks[i];
            blocks.erase(blocks.begin() + i);
            i--;
        }
    }


    ball.update();
    paddle.update();
}


void PlayState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(ball);
    game->getWindow()->draw(paddle);

    for(Block *block : blocks)
        game->getWindow()->draw(*block);

    game->getWindow()->display();
}