#include <ctime>
#include <raylib_utils.h>
#include "Game.h"

Game::Game(const int width, const int height)
{
    rg::Init();
    rl::InitWindow(width, height, "Sprout Land");
    rl::SetTargetFPS(60);
    rl::SetRandomSeed(std::time(nullptr));
    rl::InitAudioDevice();

    rg::display_surface = new rg::Surface(width, height);

    // need to init level after InitWindow()
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
        DisplayUpdate();
    }
}

void Game::UnloadResources()
{
    delete level;
    rl::CloseAudioDevice();
}

void Game::DisplayUpdate() const
{
    rg::BeginDrawingC(rl::BLACK);

    // RenderTexture renders things flipped in Y axis, we draw it "unflipped"
    // https://github.com/raysan5/raylib/issues/3803
    DrawTextureRec(
            *rg::display_surface->Texture(),
            {0, 0, (float) rg::display_surface->Texture()->width, (float) -rg::display_surface->Texture()->height},
            {0, 0}, rl::WHITE);
    rl::EndDrawing();
}
