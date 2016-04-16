#include "game.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const sf::String TITLE = "Arkanoid";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

const float BALL_VELOCITY = 8.f;
const float BALL_RADIUS = 9.f;
const float BALL_START_COORD_X = 50.f;
const float BALL_START_COORD_Y = 50.f;


const float PADDLE_VELOCITY = 6.f;
const float PADDLE_WIDTH = 60.f;
const float PADDLE_HEIGHT = 20.f;
const float PADDLE_START_COORD_X = WINDOW_WIDTH / 2.f;
const float PADDLE_START_COORD_Y = WINDOW_HEIGHT - 30.f;

const sf::Keyboard::Key BUTTON_LEFT = sf::Keyboard::Key::Left;
const sf::Keyboard::Key BUTTON_RIGHT = sf::Keyboard::Key::Right;


Game::Game() :
        AbstractGame(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, TIME_PER_FRAME),
        ball(BALL_START_COORD_X, BALL_START_COORD_Y, BALL_RADIUS, BALL_VELOCITY),
        paddle(PADDLE_START_COORD_X, PADDLE_START_COORD_Y,
               PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_VELOCITY)
{
    default_command = new DefaultCommand();
    button_left = new MoveLeftCommand();
    button_right = new MoveRightCommand();
    current_command = default_command;
}

Game::~Game() {
    if(button_left != nullptr)
        delete button_left;

    if(button_right != nullptr)
        delete button_right;

    if(default_command != nullptr)
        delete default_command;
}

bool Game::isIntersects(GameObject& first, GameObject& second)  {
    return first.getRight() >= second.getLeft() && first.getLeft() <= second.getRight() &&
           first.getBottom() >= second.getTop() && first.getTop() <= second.getBottom();
}

void Game::handlePaddleBallCollision() {

    if(!isIntersects(paddle, ball)) return;

    ball.setVelocityY(-BALL_VELOCITY);

    if(ball.getPosition().x < paddle.getPosition().x)
        ball.setVelocityX(-BALL_VELOCITY);
    else
        ball.setVelocityX(BALL_VELOCITY);
}

void Game::processEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
	    switch (event.type) 
	    {
	        case sf::Event::Closed:
	            window.close();
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


void Game::update() {
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

    handlePaddleBallCollision();

	ball.update();
    paddle.update();
}


void Game::render() {
	window.clear();
	window.draw(ball);
    window.draw(paddle);
    window.display();
}