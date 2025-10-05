#include "Drop.hpp"

Drop::Drop(
        const rg::math::Vector2<float> pos, rg::Surface *surface,
        const unsigned int z, const bool moving)
    : GenericSprite(pos, surface, z), is_alive(true), moving(moving)
{
    lifetime = rl::GetRandomValue(400, 500);
    start_time = rl::GetTime();

    if (moving)
    {
        direction = {-2, 4};
        speed = rl::GetRandomValue(200, 250);
    }
}

void Drop::Update(const float deltaTime)
{
    if (moving)
    {
        rect += direction * speed * deltaTime;
    }

    const double current_time = rl::GetTime();
    if (current_time - start_time >= lifetime / 1000.0f)
    {
        Kill();
        is_alive = false;
    }
}
