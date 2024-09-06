#include <cstring>
#include "Level.hpp"
#include "Sprites/GenericSprite.hpp"
#include "Sprites/Interaction.hpp"
#include "Sprites/Particle.hpp"
#include "Sprites/Plant.hpp"
#include "Sprites/Tree.hpp"
#include "Sprites/Water.hpp"
#include "Sprites/WildFlower.hpp"


#define RAIN_CHANCE (6)

Level::Level()
{
    soil_layer = std::make_shared<SoilLayer>(&all_sprites, &collisionSprites);
    Setup();
    overlay = std::make_shared<Overlay>(player);
    transition = std::make_shared<Transition>([this] { Reset(); }, player);
    rain = std::make_shared<Rain>(&all_sprites);
    raining = rl::GetRandomValue(0, 9) > RAIN_CHANCE;
    soil_layer->raining = raining;

    sky = std::make_shared<Sky>();
    menu = std::make_shared<Menu>(player, [this] { ToogleShop(); });

    success.SetVolume(0.3f);
    music.SetVolume(0.5f);
    music.Play();
}

Level::~Level()
{
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
    if (raining && !shop_active)
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
            auto tileSurf = std::make_shared<rg::Surface>(tileTexture, atlas_rect);
            std::make_shared<GenericSprite>(tilePos, tileSurf, order)->add(&all_sprites);
        }
    }

    // fence
    const rl::tmx_layer *fence_layer = tmx_find_layer_by_name(tmx_data, "Fence");
    auto fence_tiles = rg::tmx::GetTMXTiles(tmx_data, fence_layer);
    for (auto &[fence_pos, tileTexture, atlas_rect]: fence_tiles)
    {
        std::make_shared<GenericSprite>(
                fence_pos, std::make_shared<rg::Surface>(tileTexture, atlas_rect))
                ->add({&all_sprites, &collisionSprites});
    }

    // water
    auto waterSurfaces = rg::image::ImportFolder("resources/graphics/water");
    water_frames = rg::Frames::Merge(waterSurfaces, 1, waterSurfaces.size());
    const rl::tmx_layer *water_layer = tmx_find_layer_by_name(tmx_data, "Water");
    auto water_tiles = rg::tmx::GetTMXTiles(tmx_data, water_layer);
    for (auto &[water_pos, water_surf, atlas_pos]: water_tiles)
    {
        std::make_shared<Water>(water_pos, water_frames)->add(&all_sprites);
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
            std::make_shared<WildFlower>(
                    rg::math::Vector2{(float) decor->x, (float) (decor->y - decor->height)},
                    std::make_shared<rg::Surface>(tileTexture, atlas_rect))
                    ->add({&all_sprites, &collisionSprites});
        }
        decor = decor->next;
    }

    // collision tiles
    const rl::tmx_layer *collision_layer = tmx_find_layer_by_name(tmx_data, "Collision");
    auto collision_tiles = rg::tmx::GetTMXTiles(tmx_data, collision_layer);
    for (auto &[collision_pos, tileTexture, atlas_rect]: collision_tiles)
    {
        std::make_shared<GenericSprite>(
                collision_pos, std::make_shared<rg::Surface>(tileTexture, atlas_rect))
                ->add(&collisionSprites);
    }


    // Player
    const rl::tmx_layer *player_layer = tmx_find_layer_by_name(tmx_data, "Player");
    const auto *playerObj = player_layer->content.objgr->head;
    while (playerObj)
    {
        if (!strcmp(playerObj->name, "Start"))
        {
            player = std::make_shared<Player>(
                    rg::math::Vector2{(float) playerObj->x, (float) playerObj->y},
                    &collisionSprites, &treeSprites, &interactionSprites, soil_layer,
                    [this] { ToogleShop(); });
            player->add(&all_sprites);
        }
        if (!strcmp(playerObj->name, "Bed"))
        {
            std::make_shared<Interaction>(
                    rg::math::Vector2{(float) playerObj->x, (float) playerObj->y},
                    rg::math::Vector2{(float) playerObj->width, (float) playerObj->height},
                    playerObj->name)
                    ->add(&interactionSprites);
        }
        if (!strcmp(playerObj->name, "Trader"))
        {
            std::make_shared<Interaction>(
                    rg::math::Vector2{(float) playerObj->x, (float) playerObj->y},
                    rg::math::Vector2{(float) playerObj->width, (float) playerObj->height},
                    playerObj->name)
                    ->add(&interactionSprites);
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
            auto t = std::make_shared<Tree>(
                    rg::math::Vector2{(float) tree->x, (float) (tree->y - tree->height)},
                    std::make_shared<rg::Surface>(tileTexture, atlas_rect), tree->name,
                    [this](const std::string &item) { this->PlayerAdd(item); });
            t->add({&all_sprites, &collisionSprites, &treeSprites});
            t->CreateFruit();
        }
        tree = tree->next;
    }

    ground_surf = rg::image::Load("resources/graphics/world/ground.png");
    std::make_shared<GenericSprite>(
            rg::math::Vector2{0, 0}, ground_surf,
            LAYERS["ground"])
            ->add(&all_sprites); // GenericSprite will be deleted in ~Level.all_sprites
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
    for (const auto &treeSprite: treeSprites.Sprites())
    {
        const auto tree = std::dynamic_pointer_cast<Tree>(treeSprite);
        // remove existing apples
        for (const auto &apple: tree->apple_sprites.Sprites())
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
    for (const auto &plantSprite: soil_layer->plant_sprites.Sprites())
    {
        const auto plant = std::dynamic_pointer_cast<Plant>(plantSprite);
        if (plant->harvestable &&
            CheckCollisionRecs(plant->rect.rectangle, player->hitbox.rectangle))
        {
            PlayerAdd(plant->plant_type);
            plant->Kill();
            // we can still use plant because the deletion is delayed until dislay::Update
            std::make_shared<Particle>(plant->rect.pos, plant->image, LAYERS["main"])
                    ->add(&all_sprites);
            soil_layer->RemovePlant(plant->rect.center());
        }
    }
}

void Level::ToogleShop()
{
    shop_active = !shop_active;
}
