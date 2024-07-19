#include "Level.h"

Level::Level()
{}

void Level::run(const float dt)
{
    BeginTextureModeC(display_surface, RED);
    EndTextureModeSafe();
    all_sprites.Draw(display_surface);
    all_sprites.Update(dt);
}
