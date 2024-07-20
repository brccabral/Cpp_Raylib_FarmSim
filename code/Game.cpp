#include "Game.h"
#include <ctime>
#include "raylib_utils.h"

Game::Game(const int width, const int height)
{
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(width, height, "Sprout Land");
    SetTargetFPS(60);
    SetRandomSeed(std::time(nullptr));
    InitAudioDevice();

    display_surface = LoadRenderTexture(width, height);
    // IsRenderTextureReady does not retry nor waits for RenderTexture to be ready
    // in fact, it checks if it has an Id, Width and Height
    if (!IsRenderTextureReady(display_surface))
    {
        TraceLog(LOG_ERROR, "Could not load display_surface.");
    }

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
            display_surface.texture,
            {0, 0, (float) display_surface.texture.width, (float) -display_surface.texture.height}, {0, 0}, WHITE);
    EndDrawing();
}
