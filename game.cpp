#include "game.h"

AbstractGame::AbstractGame(unsigned int window_width, unsigned int window_height,
 	sf::String title, sf::Time time_per_frame)
	:window(sf::VideoMode(window_width, window_height), title), TimePerFrame(time_per_frame) { }


void AbstractGame::run() {
	sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	double remainder = 0.0;
	
	while (window.isOpen()) {
    	timeSinceLastUpdate += clock.restart();

    	processEvents();

	    while(timeSinceLastUpdate > TimePerFrame) {
	        update();
	        timeSinceLastUpdate -= TimePerFrame;
	    }

	    remainder = timeSinceLastUpdate.asMicroseconds() / TimePerFrame.asMicroseconds();
	   	render(remainder);
	}
}

	/*** Game implementation part ***/

Game::Game(unsigned int window_width, unsigned int window_height,
 	sf::String title, sf::Time time_per_frame) 
		: AbstractGame(window_width, window_height, title, time_per_frame),
			ball(50.f, 50.f) { }


void Game::processEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
	    switch (event.type) 
	    {
	        case sf::Event::Closed:
	            window.close();
	            break;

	        case sf::Event::KeyPressed:
	            break;

	        default:
	            break;
	    }
	}
}


void Game::update() {
	ball.update();
}


void Game::render(double remainder) {
	window.clear();
	window.draw(ball);
    window.display();
}