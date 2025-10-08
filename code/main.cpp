#include "Game.hpp"
#include "Settings.hpp"

int main()
{
    rg::Init();
    {
        const Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
        game.run();
    }
    rg::Quit();

    return 0;
}
