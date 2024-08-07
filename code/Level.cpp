#include <cstring>
#include "Level.h"
#include "Sprites/GenericSprite.h"
#include "Sprites/Interaction.h"
#include "Sprites/Particle.h"
#include "Sprites/Plant.h"
#include "Sprites/Tree.h"
#include "Sprites/Water.h"
#include "Sprites/WildFlower.h"

#define RAIN_CHANCE (6)

Level::Level()
{
    soil_layer = new SoilLayer(&all_sprites, &collisionSprites);
    Setup();
    overlay = new Overlay(player);
    transition = new Transition([this] { Reset(); }, player);
    rain = new Rain(&all_sprites);
    raining = rl::GetRandomValue(0, 9) > RAIN_CHANCE;
    soil_layer->raining = raining;

    sky = new Sky;
    menu = new Menu(player, [this] { ToogleShop(); });

    success.SetVolume(0.3f);
    music.SetVolume(0.5f);
    music.Play();
}

Level::~Level()
{
    delete overlay;
    delete transition;
    delete rain;
    delete soil_layer;
    delete sky;
    delete menu;
    delete water_frames;
    UnloadTMX(tmx_data);
}

void Level::run(const float dt)
{
    // drawing logic
    display_surface->Fill(rl::BLACK);
    all_sprites.CustomDraw(player);

    // updates
    if (shop_active)
    {
        menu->Update();
    }
    else
    {
        all_sprites.Update(dt);
        PlantCollision();
    }

    // weather
    overlay->Display();
    // rain
    if (raining and !shop_active)
    {
        rain->Update();
    }
    // day
    sky->Display(dt);

    // transition overlay
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
        for (auto &[tilePos, tileTexture, atlas_rect]: tiles)
        {
            auto tileSurf = rg::Surface::Create(tileTexture, atlas_rect);
            new GenericSprite(tilePos, tileSurf, {&all_sprites}, this, order);
        }
    }

    // fence
    const rl::tmx_layer *fence_layer = tmx_find_layer_by_name(tmx_data, "Fence");
    auto fence_tiles = rg::tmx::GetTMXTiles(tmx_data, fence_layer);
    for (auto &[fence_pos, tileTexture, atlas_rect]: fence_tiles)
    {
        new GenericSprite(
                fence_pos, rg::Surface::Create(tileTexture, atlas_rect),
                {&all_sprites, &collisionSprites}, this);
    }

    // water
    auto waterSurfaces = rg::image::ImportFolder("resources/graphics/water");
    water_frames = rg::Frames::Merge(waterSurfaces, 1, waterSurfaces.size());
    rg::image::DeleteAllVector(waterSurfaces);
    const rl::tmx_layer *water_layer = tmx_find_layer_by_name(tmx_data, "Water");
    auto water_tiles = rg::tmx::GetTMXTiles(tmx_data, water_layer);
    for (auto &[water_pos, water_surf, atlas_pos]: water_tiles)
    {
        new Water(water_pos, water_frames, {&all_sprites}, this);
    }

    // wildflowers
    const rl::tmx_layer *decor_layer = tmx_find_layer_by_name(tmx_data, "Decoration");
    const auto *decor = decor_layer->content.objgr->head;
    while (decor)
    {
        const int gid = decor->content.gid;
        if (tmx_data->tiles[gid])
        {
            rg::Rect atlas_rect{};
            auto *tileTexture = rg::tmx::GetTMXTileTexture(tmx_data->tiles[gid], &atlas_rect);
            new WildFlower(
                    {(float) decor->x, (float) (decor->y - decor->height)},
                    rg::Surface::Create(tileTexture, atlas_rect), {&all_sprites, &collisionSprites},
                    this);
        }
        decor = decor->next;
    }

    // collision tiles
    const rl::tmx_layer *collision_layer = tmx_find_layer_by_name(tmx_data, "Collision");
    auto collision_tiles = rg::tmx::GetTMXTiles(tmx_data, collision_layer);
    for (auto &[collision_pos, tileTexture, atlas_rect]: collision_tiles)
    {
        new GenericSprite(
                collision_pos, rg::Surface::Create(tileTexture, atlas_rect), {&collisionSprites},
                this);
    }


    // Player
    const rl::tmx_layer *player_layer = tmx_find_layer_by_name(tmx_data, "Player");
    const auto *playerObj = player_layer->content.objgr->head;
    while (playerObj)
    {
        if (!strcmp(playerObj->name, "Start"))
        {
            player = new Player(
                    {(float) playerObj->x, (float) playerObj->y}, &all_sprites, this,
                    &collisionSprites, &treeSprites, &interactionSprites, soil_layer,
                    [this] { ToogleShop(); });
        }
        if (!strcmp(playerObj->name, "Bed"))
        {
            new Interaction(
                    {(float) playerObj->x, (float) playerObj->y},
                    {(float) playerObj->width, (float) playerObj->height}, {&interactionSprites},
                    this, playerObj->name);
        }
        if (!strcmp(playerObj->name, "Trader"))
        {
            new Interaction(
                    {(float) playerObj->x, (float) playerObj->y},
                    {(float) playerObj->width, (float) playerObj->height}, {&interactionSprites},
                    this, playerObj->name);
        }
        playerObj = playerObj->next;
    }

    // player must exist
    if (!player)
    {
        throw;
    }

    // trees
    // Tree() depends on Player
    const rl::tmx_layer *trees_layer = tmx_find_layer_by_name(tmx_data, "Trees");
    const auto *tree = trees_layer->content.objgr->head;
    while (tree)
    {
        const int gid = tree->content.gid;
        if (tmx_data->tiles[gid])
        {
            rg::Rect atlas_rect;
            auto *tileTexture = rg::tmx::GetTMXTileTexture(tmx_data->tiles[gid], &atlas_rect);
            new Tree(
                    {(float) tree->x, (float) (tree->y - tree->height)},
                    rg::Surface::Create(tileTexture, atlas_rect),
                    {&all_sprites, &collisionSprites, &treeSprites}, this, tree->name,
                    [this](const std::string &item) { this->PlayerAdd(item); });
        }
        tree = tree->next;
    }

    ground_surf = rg::image::Load("resources/graphics/world/ground.png");
    new GenericSprite(
            {0, 0}, ground_surf, {&all_sprites}, this,
            LAYERS["ground"]); // GenericSprite will be deleted in ~Level.all_sprites
}

void Level::PlayerAdd(const std::string &item) const
{
    player->item_inventory[item] += 1;
    success.Play();
}

void Level::Reset()
{
    // plants
    soil_layer->UpdatePlants(); // must call before RemoveWater

    // apples on the trees
    for (auto *treeSprite: treeSprites.Sprites())
    {
        auto *tree = (Tree *) treeSprite;
        // remove existing apples
        for (auto *apple: tree->apple_sprites.Sprites())
        {
            apple->Kill();
        }

        // create new ones if tree is alive
        tree->CreateFruit();
    }

    // Soil
    soil_layer->RemoveAllWater();

    // randomize rain
    raining = rl::GetRandomValue(0, 9) > RAIN_CHANCE;
    soil_layer->raining = raining;
    if (raining)
    {
        soil_layer->WaterAll();
    }

    // sky
    sky->start_color = {255, 255, 255};
}

void Level::PlantCollision()
{
    for (auto *plantSprite: soil_layer->plant_sprites.Sprites())
    {
        auto *plant = (Plant *) plantSprite;
        if (plant->harvestable &&
            CheckCollisionRecs(plant->rect.rectangle, player->hitbox.rectangle))
        {
            PlayerAdd(plant->plant_type);
            plant->Kill();
            // we can still use plant because the deletion is delayed until dislay::Update
            new Particle(plant->rect.pos, plant->image, {&all_sprites}, this, LAYERS["main"]);
            soil_layer->RemovePlant(plant->rect.center());
        }
    }
}

void Level::ToogleShop()
{
    shop_active = !shop_active;
}
