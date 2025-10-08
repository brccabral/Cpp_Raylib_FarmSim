#pragma once
#include "Level.hpp"


class Game
{
public:

    Game(int width, int height);
    ~Game();
    void run() const;

private:

    // need to init level after rg::display::SetMode as it calls rl::InitWindow()
    // and InitWindow starts raylib/OpenGL resources that are needed in Level()
    Level *level = nullptr;
};
