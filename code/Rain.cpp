#include "Rain.hpp"
#include "Sprites/Drop.hpp"


Rain::Rain(CameraGroup *all_sprites) : all_sprites(all_sprites)
{
    rain_drops = rg::image::ImportFolder("resources/graphics/rain/drops");
    rain_floor = rg::image::ImportFolder("resources/graphics/rain/floor");

    const auto ground = rg::image::Load("resources/graphics/world/ground.png");
    ground_w = ground.GetRect().width;
    ground_h = ground.GetRect().height;
    drops_sprites_.resize(ground_h * ground_w);
}

void Rain::Update()
{
    CreateFloor();
    CreateDrops();
}

void Rain::CreateFloor()
{
    const unsigned int random_floor = rl::GetRandomValue(0, rain_floor.size() - 1);
    const int x = rl::GetRandomValue(0, ground_w);
    const int y = rl::GetRandomValue(0, ground_h);
    for (size_t i = 0; i < drops_sprites_.size(); ++i)
    {
        if (!drops_sprites_[i].is_alive)
        {
            drops_sprites_[i] = Drop(
                    rg::math::Vector2{(float) x, (float) y}, &rain_floor[random_floor],
                    LAYERS["rain floor"], false);
            drops_sprites_[i].add(all_sprites);
            break;
        }
    }
}

void Rain::CreateDrops()
{
    const unsigned int random_drop = rl::GetRandomValue(0, rain_drops.size() - 1);
    const int x = rl::GetRandomValue(0, ground_w);
    const int y = rl::GetRandomValue(0, ground_h);
    for (size_t i = 0; i < drops_sprites_.size(); ++i)
    {
        if (!drops_sprites_[i].is_alive)
        {
            drops_sprites_[i] = Drop(
                    rg::math::Vector2{(float) x, (float) y}, &rain_drops[random_drop],
                    LAYERS["rain drops"], true);
            drops_sprites_[i].add(all_sprites);
            break;
        }
    }
}
