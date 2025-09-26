#include <rygame.hpp>
#include "Game.hpp"

Game::Game(const int width, const int height)
{
    rg::Init();
    rg::display::SetMode(width, height);
    rg::display::SetCaption("Farmew Valley");

    // need to init level after rg::display::SetMode as it calls rl::InitWindow()
    // and InitWindow starts raylib/OpenGL resources that are needed in Level()
    level = new Level();
}

Game::~Game()
{
    Settings::Destroy();
    delete level;
    rg::Quit();
}

void Game::run() const
{
    while (!rg::WindowCloseOrQuit())
    {
        level->run(rl::GetFrameTime());
        rg::display::Update();
    }
}

Settings *Settings::instance = nullptr;
