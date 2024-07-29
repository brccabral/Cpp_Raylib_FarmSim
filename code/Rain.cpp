#include "Rain.h"
#include "Sprites/Drop.h"


Rain::Rain(CameraGroup *all_sprites) : all_sprites(all_sprites)
{
    rain_drops = rg::assets::ImportFolder("resources/graphics/rain/drops");
    rain_floor = rg::assets::ImportFolder("resources/graphics/rain/floor");

    const rg::Surface *ground = rg::Surface::Load("resources/graphics/world/ground.png");
    ground_w = ground->GetRect().width;
    ground_h = ground->GetRect().height;
    delete ground;
}

Rain::~Rain()
{
    for (const auto *surface: rain_drops)
    {
        delete surface;
    }
    for (const auto *surface: rain_floor)
    {
        delete surface;
    }
}

void Rain::Update()
{
    CreateFloor();
    CreateDrops();
}

void Rain::CreateFloor()
{
    const unsigned int random_floor = rl::GetRandomValue(0, rain_floor.size() - 1);
    const float x = rl::GetRandomValue(0, ground_w);
    const float y = rl::GetRandomValue(0, ground_h);
    new Drop({x, y}, rain_floor[random_floor], {all_sprites}, LAYERS["rain floor"], false);
}

void Rain::CreateDrops()
{
    const unsigned int random_drop = rl::GetRandomValue(0, rain_drops.size() - 1);
    const float x = rl::GetRandomValue(0, ground_w);
    const float y = rl::GetRandomValue(0, ground_h);
    new Drop({x, y}, rain_drops[random_drop], {all_sprites}, LAYERS["rain drops"], true);
}
