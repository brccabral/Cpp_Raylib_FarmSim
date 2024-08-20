#include <rygame.hpp>
#include "Game.hpp"

Game::Game(const int width, const int height)
{
    rg::Init();
    rg::display::SetMode(width, height);
    rg::display::SetCaption("Sprout Land");

    // need to init level after rg::display::SetMode as it calls rl::InitWindow()
    // and InitWindow starts raylib resources that are needed in Level()
    level = new Level();
}

Game::~Game()
{
    delete level;
    rg::Quit();
}

void Game::run() const
{
    while (!rl::WindowShouldClose())
    {
        level->run(rl::GetFrameTime());
        rg::display::Update();
    }
}
