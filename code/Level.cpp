#include "Level.h"

Level::Level()
{
    Setup();
    overlay = new Overlay(player);
}

Level::~Level()
{
    delete player;
    delete overlay;
}

void Level::run(const float dt)
{
    display_surface->Fill(BLACK);
    all_sprites.Draw(display_surface);
    all_sprites.Update(dt);
    overlay->Display();
}

void Level::Setup()
{
    player = new Player({640, 360}, &all_sprites);
}
