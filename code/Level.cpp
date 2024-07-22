#include <raylib-tmx.h>
#include "Level.h"
#include "Sprites/GenericSprite.h"
#include "Sprites/Tree.h"
#include "Sprites/Water.h"
#include "Sprites/WildFlower.h"

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
        // can't draw as a single sprite because we need to sort them on Y before drawing
        auto tiles = GetTMXTiles(tmx_data, layer);
        for (auto &[tilePos, tileSurf]: tiles)
        {
            new GenericSprite(tilePos, tileSurf, {&all_sprites}, order);
        }
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

    // wildflowers
    const tmx_layer *decor_layer = tmx_find_layer_by_name(tmx_data, "Decoration");
    auto *decorObj = decor_layer->content.objgr->head;
    std::vector<tmx_object *> reverseDecorOrder{};
    while (decorObj)
    {
        reverseDecorOrder.push_back(decorObj);
        decorObj = decorObj->next;
    }
    for (int i = reverseDecorOrder.size() - 1; i >= 0; --i)
    {
        const auto *decor = reverseDecorOrder[i];

        const int gid = decor->content.gid;
        if (tmx_data->tiles[gid])
        {
            auto *surf = GetTMXTileSurface(tmx_data->tiles[gid]);
            new WildFlower({(float) decor->x, (float) (decor->y - decor->height)}, surf, {&all_sprites});
        }
    }

    // trees
    const tmx_layer *trees_layer = tmx_find_layer_by_name(tmx_data, "Trees");
    auto *treeObj = trees_layer->content.objgr->head;
    std::vector<tmx_object *> reverseTreeOrder{};
    while (treeObj)
    {
        reverseTreeOrder.push_back(treeObj);
        treeObj = treeObj->next;
    }
    for (int i = reverseTreeOrder.size() - 1; i >= 0; --i)
    {
        const auto *tree = reverseTreeOrder[i];

        const int gid = tree->content.gid;
        if (tmx_data->tiles[gid])
        {
            auto *surf = GetTMXTileSurface(tmx_data->tiles[gid]);
            new Tree({(float) tree->x, (float) (tree->y - tree->height)}, surf, {&all_sprites}, tree->name);
        }
    }


    player = new Player({640, 360}, all_sprites);

    auto *surface = Surface::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, surface, {&all_sprites},
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}
