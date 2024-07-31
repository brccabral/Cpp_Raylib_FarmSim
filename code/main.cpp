#include "Game.h"
#include "Settings.h"

int main()
{
    const Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.run();

    return 0;
}
