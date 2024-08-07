#pragma once
#include "Level.h"


class Game
{
public:

    Game(int width, int height);
    ~Game();
    void run() const;

private:

    void UnloadResources();

    Level *level = nullptr;
};
