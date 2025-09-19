#pragma once
#include "Level.hpp"


class Game
{
public:

    Game(int width, int height);
    ~Game();
    void run();

private:

    Level level{};
};
