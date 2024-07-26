#include <cstring>
#include "Level.h"
#include "Sprites/GenericSprite.h"
#include "Sprites/Interaction.h"
#include "Sprites/Tree.h"
#include "Sprites/Water.h"
#include "Sprites/WildFlower.h"


Level::Level()
{
    display_surface = rg::display::GetSurface();

    soil_layer = new SoilLayer(&all_sprites);
    Setup();
    overlay = new Overlay(player);
    transition = new Transition(
            [this]
            {
                Reset();
            }, player);
    rain = new Rain(&all_sprites);
    raining = rl::GetRandomValue(0, 10) > 3;
    soil_layer->raining = raining;
}

Level::~Level()
{
    // deletes all water_frames, the Water class don't need to delete them
    // but need to set image to nullptr
    for (const auto *surface: water_frames)
    {
        delete surface;
    }

    delete overlay;
    delete transition;
    delete rain;
    UnloadTMX(tmx_data);
}

void Level::run(const float dt)
{
    display_surface->Fill(rl::BLACK);
    all_sprites.CustomDraw(player);
    all_sprites.Update(dt);
    overlay->Display();

    if (raining)
    {
        rain->Update();
    }

    if (player->sleep)
    {
        transition->Play();
    }
}

void Level::Setup()
{
    tmx_data = rl::LoadTMX("resources/data/map.tmx");

    // static layers
    const std::vector<std::pair<std::string, unsigned int>> layers = {
            {"HouseFloor", LAYERS["house floor"]}, //
            {"HouseFurnitureBottom", LAYERS["house bottom"]}, //
            {"HouseWalls", LAYERS["main"]}, //
            {"HouseFurnitureTop", LAYERS["main"]}, //
    };
    for (auto &[layer_name, order]: layers)
    {
        const rl::tmx_layer *layer = tmx_find_layer_by_name(tmx_data, layer_name.c_str());
        // can't draw as a single sprite because we need to sort them on Y before drawing
        auto tiles = rg::tmx::GetTMXTiles(tmx_data, layer);
        for (auto &[tilePos, tileSurf]: tiles)
        {
            new GenericSprite(tilePos, tileSurf, {&all_sprites}, order);
        }
    }

    // fence
    const rl::tmx_layer *fence_layer = tmx_find_layer_by_name(tmx_data, "Fence");
    auto fence_tiles = rg::tmx::GetTMXTiles(tmx_data, fence_layer);
    for (auto &[fence_pos, fence_surf]: fence_tiles)
    {
        new GenericSprite(fence_pos, fence_surf, {&all_sprites, &collisionSprites});
    }

    // water
    water_frames = rg::assets::ImportFolder("resources/graphics/water");
    const rl::tmx_layer *water_layer = tmx_find_layer_by_name(tmx_data, "Water");
    auto water_tiles = rg::tmx::GetTMXTiles(tmx_data, water_layer);
    for (auto &[water_pos, water_surf]: water_tiles)
    {
        new Water(water_pos, water_frames, {&all_sprites});
        delete water_surf;
    }

    // wildflowers
    const rl::tmx_layer *decor_layer = tmx_find_layer_by_name(tmx_data, "Decoration");
    const auto *decor = decor_layer->content.objgr->head;
    while (decor)
    {
        const int gid = decor->content.gid;
        if (tmx_data->tiles[gid])
        {
            auto *surf = rg::tmx::GetTMXTileSurface(tmx_data->tiles[gid]);
            new WildFlower(
                    {(float) decor->x, (float) (decor->y - decor->height)}, surf,
                    {&all_sprites, &collisionSprites});
        }
        decor = decor->next;
    }

    // trees
    const rl::tmx_layer *trees_layer = tmx_find_layer_by_name(tmx_data, "Trees");
    const auto *tree = trees_layer->content.objgr->head;
    while (tree)
    {
        const int gid = tree->content.gid;
        if (tmx_data->tiles[gid])
        {
            auto *surf = rg::tmx::GetTMXTileSurface(tmx_data->tiles[gid]);
            new Tree(
                    {(float) tree->x, (float) (tree->y - tree->height)}, surf,
                    {&all_sprites, &collisionSprites, &treeSprites}, tree->name,
                    [this](const std::string &item)
                    {
                        this->PlayerAdd(item);
                    });
        }
        tree = tree->next;
    }

    // collision tiles
    const rl::tmx_layer *collision_layer = tmx_find_layer_by_name(tmx_data, "Collision");
    auto collision_tiles = rg::tmx::GetTMXTiles(tmx_data, collision_layer);
    for (auto &[collision_pos, collision_surf]: collision_tiles)
    {
        new GenericSprite(collision_pos, collision_surf, {&collisionSprites});
    }


    // Player
    const rl::tmx_layer *player_layer = tmx_find_layer_by_name(tmx_data, "Player");
    const auto *playerObj = player_layer->content.objgr->head;
    while (playerObj)
    {
        if (!strcmp(playerObj->name, "Start"))
        {
            player = new Player(
                    {(float) playerObj->x, (float) playerObj->y}, all_sprites, &collisionSprites,
                    &treeSprites, &interactionSprites, soil_layer);
        }
        if (!strcmp(playerObj->name, "Bed"))
        {
            new Interaction(
                    {(float) playerObj->x, (float) playerObj->y},
                    {(float) playerObj->width, (float) playerObj->height}, {&interactionSprites},
                    playerObj->name);
        }
        playerObj = playerObj->next;
    }


    auto *surface = rg::Surface::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, surface, {&all_sprites},
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}

void Level::PlayerAdd(const std::string &item)
{
    player->item_inventory[item] += 1;
}

void Level::Reset()
{
    // apples on the trees
    for (auto *treeSprite: treeSprites.sprites)
    {
        auto *tree = (Tree *) treeSprite;
        for (auto *apple: tree->apple_sprites.sprites)
        {
            apple->Kill();
        }
        tree->CreateFruit();
    }

    // Soil
    soil_layer->RemoveWater();

    // randomize rain
    raining = rl::GetRandomValue(0, 10) > 3;
    soil_layer->raining = raining;
    if (raining)
    {
        soil_layer->WaterAll();
    }

}
