#include <raylib_utils.h>
#include "Game.h"

Game::Game(const int width, const int height)
{
    rg::Init();
    rg::display::SetMode(width, height);
    rg::display::SetCaption("Sprout Land");
    rl::InitAudioDevice();

    // need to init level after rg::display::SetMode as it calls rl::InitWindow()
    // and InitWindow starts raylib resources that are needed in Level()
    level = new Level();
}

Game::~Game()
{
    UnloadResources();
    rl::CloseWindow();
}

void Game::run()
{
    while (!rl::WindowShouldClose())
    {
        level->run(rl::GetFrameTime());
        rg::display::Update();
    }
}

void Game::UnloadResources()
{
    delete level;
    rl::CloseAudioDevice();
}
