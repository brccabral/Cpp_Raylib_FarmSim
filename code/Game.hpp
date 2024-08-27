#pragma once
#include "Level.hpp"


class Game
{
public:

    Game(int width, int height);
    ~Game();
    void run() const;

private:

    void UnloadResources();

    std::shared_ptr<Level> level = nullptr;
};
