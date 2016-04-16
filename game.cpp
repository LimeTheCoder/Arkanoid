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
               PADDLE_WIDTH, PADDLE_HEIGHT) { }


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
        paddle.setVelocityX(-PADDLE_VELOCITY);
    else if(sf::Keyboard::isKeyPressed(BUTTON_RIGHT) &&
            paddle.getRight() < WINDOW_WIDTH)
        paddle.setVelocityX(PADDLE_VELOCITY);
    else
        paddle.setVelocityX(0.f);
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

	ball.update();
    paddle.update();
}


void Game::render() {
	window.clear();
	window.draw(ball);
    window.draw(paddle);
    window.display();
}