#ifndef ABSRACT_GAME_H
#define ABSRACT_GAME_H

#include <SFML/Graphics.hpp>


class AbstractGame {
public:
    AbstractGame(float window_width, float window_height,
                 sf::String title, sf::Time time_per_frame);
    void run();

protected:
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void processEvents() = 0;

    sf::RenderWindow window;
    const sf::Time TimePerFrame;
};

#endif
