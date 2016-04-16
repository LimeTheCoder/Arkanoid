#include "game.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main()
{
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT);

    game.run();

    return 0;
}