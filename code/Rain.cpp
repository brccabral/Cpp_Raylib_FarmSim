#include "Rain.hpp"
#include "Sprites/Drop.hpp"


Rain::Rain(
        CameraGroup *all_sprites, const unsigned int ground_width,
        const unsigned int ground_height) : all_sprites(all_sprites), ground_width(ground_width),
                                            ground_height(ground_height)
{
    rain_drops = rg::image::LoadFolderList("resources/graphics/rain/drops");
    rain_floor = rg::image::LoadFolderList("resources/graphics/rain/floor");

    drops_sprites_.resize(200);
}

void Rain::Update()
{
    CreateFloor();
    CreateDrops();
}

void Rain::CreateFloor()
{
    const unsigned int random_floor = rl::GetRandomValue(0, rain_floor.size() - 1);
    const int x = rl::GetRandomValue(0, ground_width);
    const int y = rl::GetRandomValue(0, ground_height);
    for (auto &drop: drops_sprites_)
    {
        if (!drop.is_alive)
        {
            drop = Drop(
                    rg::math::Vector2{(float) x, (float) y}, &rain_floor[random_floor],
                    Settings::GetInstance().LAYERS["rain floor"], false);
            drop.add(all_sprites);
            break;
        }
    }
}

void Rain::CreateDrops()
{
    const unsigned int random_drop = rl::GetRandomValue(0, rain_drops.size() - 1);
    const int x = rl::GetRandomValue(0, ground_width);
    const int y = rl::GetRandomValue(0, ground_height);
    for (auto &drop: drops_sprites_)
    {
        if (!drop.is_alive)
        {
            drop = Drop(
                    rg::math::Vector2{(float) x, (float) y}, &rain_drops[random_drop],
                    Settings::GetInstance().LAYERS["rain drops"], true);
            drop.add(all_sprites);
            break;
        }
    }
}
