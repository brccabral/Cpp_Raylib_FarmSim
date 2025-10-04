#include <cstring>
#include "Level.hpp"


#define RAIN_CHANCE (6)

Level::Level()
{
    Setup();
    soil_layer = SoilLayer(&all_sprites, &collisionSprites);
    overlay = Overlay(player);
    transition = Transition(
            [this]
            {
                Reset();
            }, player);
    rain = Rain(&all_sprites);
    raining = rl::GetRandomValue(0, 9) > RAIN_CHANCE;
    soil_layer.raining = raining;

    menu = Menu(
            player, [this]
            {
                ToogleShop();
            });

    success.SetVolume(0.3f);
    music.SetVolume(0.5f);
    music.Play();
}

Level::~Level()
{
    delete player;
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
        menu.Update();
    }
    else
    {
        all_sprites.Update(dt);
        PlantCollision();
    }

    // weather
    overlay.Display();
    // rain
    if (raining && !shop_active)
    {
        rain.Update();
    }
    // day
    sky.Display(dt);

    // transition overlay
    if (player->sleep)
    {
        transition.Play();
    }
}

void Level::Setup()
{
    tmx_data = rl::LoadTMX("resources/data/map.tmx");
    level_surfaces = rg::tmx::GetTMXSurfaces(tmx_data);
    generic_sprites_.reserve(tmx_data->width * tmx_data->height * 6);
    water_sprites_.reserve(tmx_data->width * tmx_data->height);
    wild_flowers_sprites_.reserve(tmx_data->width * tmx_data->height);
    trees_sprites_.reserve(tmx_data->width * tmx_data->height);
    interactions_sprites_.reserve(tmx_data->width * tmx_data->height);
    particle_sprites_.resize(20);

    all_sprites.reserve(tmx_data->width * tmx_data->height * 6);
    collisionSprites.reserve(tmx_data->width * tmx_data->height);
    treeSprites.reserve(tmx_data->width * tmx_data->height);
    interactionSprites.reserve(tmx_data->width * tmx_data->height);

    // static layers
    const std::vector<std::pair<std::string, unsigned int>> layers = {
            {"HouseFloor", Settings::GetInstance().LAYERS["house floor"]}, //
            {"HouseFurnitureBottom", Settings::GetInstance().LAYERS["house bottom"]}, //
            {"HouseWalls", Settings::GetInstance().LAYERS["main"]}, //
            {"HouseFurnitureTop", Settings::GetInstance().LAYERS["main"]}, //
    };
    for (auto &[layer_name, order]: layers)
    {
        const rl::tmx_layer *layer = tmx_find_layer_by_name(tmx_data, layer_name.c_str());
        // can't draw as a single sprite because we need to sort them on Y before drawing
        auto tiles = rg::tmx::GetTMXTiles(tmx_data, layer);
        for (auto &[tilePos, gid]: tiles)
        {
            generic_sprites_.emplace_back(tilePos, &level_surfaces[gid], order).add(&all_sprites);
        }
    }

    // fence
    const rl::tmx_layer *fence_layer = tmx_find_layer_by_name(tmx_data, "Fence");
    auto fence_tiles = rg::tmx::GetTMXTiles(tmx_data, fence_layer);
    for (auto &[fence_pos, gid]: fence_tiles)
    {
        generic_sprites_.emplace_back(fence_pos, &level_surfaces[gid]).add(
                {&all_sprites, &collisionSprites});
    }

    // water
    const auto waterSurfaces = rg::image::ImportFolder("resources/graphics/water");
    water_frames = rg::Frames::Merge(waterSurfaces, 1, waterSurfaces.size());
    const rl::tmx_layer *water_layer = tmx_find_layer_by_name(tmx_data, "Water");
    auto water_tiles = rg::tmx::GetTMXTiles(tmx_data, water_layer);
    for (auto &[water_pos, gid]: water_tiles)
    {
        water_sprites_.emplace_back(water_pos, &water_frames).add(&all_sprites);
    }

    // wildflowers
    const rl::tmx_layer *decor_layer = tmx_find_layer_by_name(tmx_data, "Decoration");
    const auto *decor = decor_layer->content.objgr->head;
    while (decor)
    {
        if (const int gid = decor->content.gid)
        {
            const auto pos = rg::math::Vector2
                    {(float) decor->x, (float) (decor->y - decor->height)};
            wild_flowers_sprites_.emplace_back(pos, &level_surfaces[gid]).add(
                    {&all_sprites, &collisionSprites});
        }
        decor = decor->next;
    }

    // collision tiles
    const rl::tmx_layer *collision_layer = tmx_find_layer_by_name(tmx_data, "Collision");
    auto collision_tiles = rg::tmx::GetTMXTiles(tmx_data, collision_layer);
    for (auto &[collision_pos, gid]: collision_tiles)
    {
        generic_sprites_.emplace_back(collision_pos, &level_surfaces[gid]).add(&collisionSprites);
    }


    // Player
    const rl::tmx_layer *player_layer = tmx_find_layer_by_name(tmx_data, "Player");
    const auto *playerObj = player_layer->content.objgr->head;
    while (playerObj)
    {
        if (!strcmp(playerObj->name, "Start"))
        {
            player = new Player(
                    rg::math::Vector2{(float) playerObj->x, (float) playerObj->y},
                    &collisionSprites, &treeSprites, &interactionSprites, &soil_layer,
                    [this]
                    {
                        ToogleShop();
                    });
            player->add(&all_sprites);
        }
        if (!strcmp(playerObj->name, "Bed"))
        {
            interactions_sprites_.emplace_back(
                    rg::math::Vector2{(float) playerObj->x, (float) playerObj->y},
                    rg::math::Vector2{(float) playerObj->width, (float) playerObj->height},
                    playerObj->name).add(&interactionSprites);
        }
        if (!strcmp(playerObj->name, "Trader"))
        {
            interactions_sprites_.emplace_back(
                    rg::math::Vector2{(float) playerObj->x, (float) playerObj->y},
                    rg::math::Vector2{(float) playerObj->width, (float) playerObj->height},
                    playerObj->name).add(&interactionSprites);
        }
        playerObj = playerObj->next;
    }

    // trees
    stump_surfaces = rg::image::LoadFolderDict("resources/graphics/stumps");
    apple_surf = rg::image::Load("resources/graphics/fruit/apple.png");
    // Tree() depends on Player
    const rl::tmx_layer *trees_layer = tmx_find_layer_by_name(tmx_data, "Trees");
    const auto *tree = trees_layer->content.objgr->head;
    while (tree)
    {
        if (const int gid = tree->content.gid)
        {
            const auto pos = rg::math::Vector2{(float) tree->x, (float) (tree->y - tree->height)};
            trees_sprites_.emplace_back(
                    pos, &level_surfaces[gid], &apple_surf, &stump_surfaces[tree->name],
                    tree->name, &all_sprites,
                    [this](const std::string &item)
                    {
                        this->PlayerAdd(item);
                    }).add({&all_sprites, &collisionSprites, &treeSprites});
            trees_sprites_.back().CreateFruit();
        }
        tree = tree->next;
    }

    ground_surf = rg::image::Load("resources/graphics/world/ground.png");
    generic_sprites_.emplace_back(
            rg::math::Vector2<float>{}, &ground_surf,
            Settings::GetInstance().LAYERS["ground"]).add(&all_sprites);
}

void Level::PlayerAdd(const std::string &item) const
{
    player->item_inventory[item] += 1;
    success.Play();
}

void Level::Reset()
{
    // plants
    soil_layer.UpdatePlants(); // must call before RemoveWater

    // apples on the trees
    for (auto *treeSprite: treeSprites.Sprites())
    {
        const auto tree = dynamic_cast<Tree *>(treeSprite);
        // remove existing apples
        for (auto *apple: tree->apple_sprites.Sprites())
        {
            apple->Kill();
        }

        // create new ones if tree is alive
        tree->CreateFruit();
    }

    // Soil
    soil_layer.RemoveAllWater();

    // randomize rain
    raining = rl::GetRandomValue(0, 9) > RAIN_CHANCE;
    soil_layer.raining = raining;
    if (raining)
    {
        soil_layer.WaterAll();
    }

    // sky
    sky.start_color = {255, 255, 255};
}

void Level::PlantCollision()
{
    for (auto *plantSprite: soil_layer.plant_sprites.Sprites())
    {
        const auto plant = dynamic_cast<Plant *>(plantSprite);
        if (plant->harvestable &&
            CheckCollisionRecs(plant->rect.rectangle, player->hitbox.rectangle))
        {
            PlayerAdd(plant->plant_type);
            plant->Kill();
            // we can still use plant because the deletion is delayed until dislay::Update
            for (auto &ps: particle_sprites_)
            {
                if (!ps.is_alive)
                {
                    ps = Particle(
                            plant->rect.pos, plant->image, Settings::GetInstance().LAYERS["main"]);
                    ps.add(&all_sprites);
                    break;
                }
            }
            soil_layer.RemovePlant(plant->rect.center());
        }
    }
}

void Level::ToogleShop()
{
    shop_active = !shop_active;
}
