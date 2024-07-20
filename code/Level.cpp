#include "Level.h"

Level::Level()
{
    Setup();
}

Level::~Level()
{
    delete player;
}

void Level::run(const float dt)
{
    BeginTextureModeC(display_surface, BLACK);
    EndTextureModeSafe();
    all_sprites.Draw(display_surface);
    all_sprites.Update(dt);
}

void Level::Setup()
{
    player = new Player({640, 360}, &all_sprites);
}
