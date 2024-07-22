#include <raylib-tmx.h>
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
    all_sprites.CustomDraw(player);
    all_sprites.Update(dt);
    overlay->Display();
}

void Level::Setup()
{
    const auto *tmx_data = LoadTMX("resources/data/map.tmx");

    // house
    const std::vector<std::pair<std::string, unsigned int>> houseLayers = {
            {"HouseFloor", LAYERS["house bottom"]}, //
            {"HouseFurnitureBottom", LAYERS["house bottom"]}, //
            {"HouseWalls", LAYERS["main"]}, //
            {"HouseFurnitureTop", LAYERS["main"]}, //
    };
    for (auto &[house_layer, order]: houseLayers)
    {
        const tmx_layer *house_tmx = tmx_find_layer_by_name(tmx_data, house_layer.c_str());

        auto *house_surf = GetTMXLayerSurface(tmx_data, house_tmx);
        new GenericSprite({0, 0}, house_surf, {&all_sprites}, order);
    }

    player = new Player({640, 360}, all_sprites);

    auto *surface = Surface::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, surface, {&all_sprites},
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}
