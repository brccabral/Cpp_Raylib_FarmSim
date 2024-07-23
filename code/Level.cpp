#include <raylib-tmx.h>
#include "Level.h"
#include "Sprites/GenericSprite.h"
#include "Sprites/Tree.h"
#include "Sprites/Water.h"
#include "Sprites/WildFlower.h"

#include <cstring>

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
    all_sprites.DeleteAll();
    // some sprites might be in collisionSprites, but not in all_sprites
    // those that are in both, when they are deleted from all_sprites, they are
    // removed from collisionSprites to avoid double free
    collisionSprites.DeleteAll();

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
            {"HouseFloor", LAYERS["house floor"]}, //
            {"HouseFurnitureBottom", LAYERS["house bottom"]}, //
            {"HouseWalls", LAYERS["main"]}, //
            {"HouseFurnitureTop", LAYERS["main"]}, //
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

    // fence
    const tmx_layer *fence_layer = tmx_find_layer_by_name(tmx_data, "Fence");
    auto fence_tiles = GetTMXTiles(tmx_data, fence_layer);
    for (auto &[fence_pos, fence_surf]: fence_tiles)
    {
        new GenericSprite(fence_pos, fence_surf, {&all_sprites, &collisionSprites});
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
    const auto *decor = decor_layer->content.objgr->head;
    while (decor)
    {
        const int gid = decor->content.gid;
        if (tmx_data->tiles[gid])
        {
            auto *surf = GetTMXTileSurface(tmx_data->tiles[gid]);
            new WildFlower(
                    {(float) decor->x, (float) (decor->y - decor->height)}, surf, {&all_sprites, &collisionSprites});
        }
        decor = decor->next;
    }

    // trees
    const tmx_layer *trees_layer = tmx_find_layer_by_name(tmx_data, "Trees");
    const auto *tree = trees_layer->content.objgr->head;
    while (tree)
    {
        const int gid = tree->content.gid;
        if (tmx_data->tiles[gid])
        {
            auto *surf = GetTMXTileSurface(tmx_data->tiles[gid]);
            new Tree(
                    {(float) tree->x, (float) (tree->y - tree->height)}, surf, {&all_sprites, &collisionSprites},
                    tree->name);
        }
        tree = tree->next;
    }

    // collision tiles
    const tmx_layer *collision_layer = tmx_find_layer_by_name(tmx_data, "Collision");
    auto collision_tiles = GetTMXTiles(tmx_data, collision_layer);
    for (auto &[collision_pos, collision_surf]: collision_tiles)
    {
        new GenericSprite(collision_pos, collision_surf, {&collisionSprites});
    }


    // Player
    const tmx_layer *player_layer = tmx_find_layer_by_name(tmx_data, "Player");
    const auto *playerObj = player_layer->content.objgr->head;
    while (playerObj)
    {
        if (!strcmp(playerObj->name, "Start"))
        {
            player = new Player({(float) playerObj->x, (float) playerObj->y}, all_sprites, &collisionSprites);
        }
        playerObj = playerObj->next;
    }


    auto *surface = Surface::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, surface, {&all_sprites},
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}
