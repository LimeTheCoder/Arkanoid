#ifndef GAME_H
#define GAME_H

#include "ball.h"


class AbstractGame {
public:
	void run();
	AbstractGame(unsigned int window_width, unsigned int window_height,
		sf::String title, sf::Time time_per_frame);

protected:
	virtual void render(double) = 0;
	virtual void update() = 0;
	virtual void processEvents() = 0;
	
	sf::RenderWindow window;
	const sf::Time TimePerFrame;
};


class Game : public AbstractGame {
public:
	Game(unsigned int window_width, unsigned int window_height,
		sf::String title = "Arkanoid", sf::Time time_per_frame = sf::seconds(1.f / 60.f));

	void render(double);
	void update();
	void processEvents();

private:
	Ball ball;

};

#endif
