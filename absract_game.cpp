#include "absract_game.h"

AbstractGame::AbstractGame(unsigned int window_width, unsigned int window_height,
                           sf::String title, sf::Time time_per_frame)
        :window(sf::VideoMode(window_width, window_height), title), TimePerFrame(time_per_frame) { }


void AbstractGame::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        processEvents();

        while(timeSinceLastUpdate > TimePerFrame) {
            update();
            timeSinceLastUpdate -= TimePerFrame;
        }

        render();
    }
}