#include <ctime>
#include <raylib_utils.h>
#include "Game.h"

Game::Game(const int width, const int height)
{
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(width, height, "Sprout Land");
    SetTargetFPS(60);
    SetRandomSeed(std::time(nullptr));
    InitAudioDevice();

    display_surface = new Surface(width, height);

    // need to init level after InitWindow()
    level = new Level();
}

Game::~Game()
{
    UnloadResources();
    CloseWindow();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        level->run(GetFrameTime());
        DisplayUpdate();
    }
}

void Game::UnloadResources()
{
    delete level;
    CloseAudioDevice();
}

void Game::DisplayUpdate() const
{
    BeginDrawingC(BLACK);

    // RenderTexture renders things flipped in Y axis, we draw it "unflipped"
    // https://github.com/raysan5/raylib/issues/3803
    DrawTextureRec(
            *display_surface->Texture(),
            {0, 0, (float) display_surface->Texture()->width, (float) -display_surface->Texture()->height}, {0, 0},
            WHITE);
    EndDrawing();
}
