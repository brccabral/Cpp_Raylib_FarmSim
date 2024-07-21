#include "Level.h"
#include "GenericSprite.h"

Level::Level()
{
    Setup();
    overlay = new Overlay(player);
}

Level::~Level()
{
    // deletes player and all sprites
    for (const auto *sprite: all_sprites.sprites)
    {
        delete sprite;
    }
    delete overlay;
}

void Level::run(const float dt)
{
    display_surface->Fill(BLACK);
    all_sprites.CustomDraw();
    all_sprites.Update(dt);
    overlay->Display();
}

void Level::Setup()
{
    player = new Player({640, 360}, all_sprites);

    auto *surface = Surface::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, surface, {&all_sprites},
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}
