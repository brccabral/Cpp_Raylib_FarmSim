#include <raylib-tmx.h>
#include "Level.h"
#include "Sprites/GenericSprite.h"
#include "Sprites/Water.h"

Level::Level()
{
    Setup();
    overlay = new Overlay(player);
}

Level::~Level()
{
    // deletes all water_frames, the Water class don't need to delete them
    // but need to set image to nullptr
    for (const auto *surface: water_frames)
    {
        delete surface;
    }
    // deletes player and all sprites
    for (const auto *sprite: all_sprites.sprites)
    {
        delete sprite;
    }
    delete overlay;
    UnloadTMX(tmx_data);
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
    tmx_data = LoadTMX("resources/data/map.tmx");

    // static layers
    const std::vector<std::pair<std::string, unsigned int>> layers = {
            {"HouseFloor", LAYERS["house bottom"]}, //
            {"HouseFurnitureBottom", LAYERS["house bottom"]}, //
            {"HouseWalls", LAYERS["main"]}, //
            {"HouseFurnitureTop", LAYERS["main"]}, //
            {"Fence", LAYERS["main"]}, //
    };
    for (auto &[layer_name, order]: layers)
    {
        const tmx_layer *layer = tmx_find_layer_by_name(tmx_data, layer_name.c_str());
        auto *surf = GetTMXLayerSurface(tmx_data, layer);
        new GenericSprite({0, 0}, surf, {&all_sprites}, order);
    }

    // water
    water_frames = ImportFolder("resources/graphics/water");
    const tmx_layer *water_layer = tmx_find_layer_by_name(tmx_data, "Water");
    auto water_tiles = GetTMXTiles(tmx_data, water_layer);
    for (auto &[water_pos, water_surf]: water_tiles)
    {
        new Water(water_pos, water_frames, {&all_sprites});
        delete water_surf;
    }

    player = new Player({640, 360}, all_sprites);

    auto *surface = Surface::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, surface, {&all_sprites},
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}
