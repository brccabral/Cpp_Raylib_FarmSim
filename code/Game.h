#pragma once
#include "Level.h"


class Game
{
public:

    Game(int width, int height);
    ~Game();
    void run();

private:

    void UnloadResources();
    void DisplayUpdate() const;

    Level *level = nullptr;
};
