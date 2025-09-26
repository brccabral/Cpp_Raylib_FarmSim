#include "Game.hpp"
#include "Settings.hpp"

int main()
{
    const Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.run();

    return 0;
}
