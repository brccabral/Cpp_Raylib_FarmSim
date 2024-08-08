#include "Drop.h"

Drop::Drop(
        const rg::math::Vector2 pos, rg::Surface *surface,
        const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner,
        const unsigned int z, const bool moving)
    : GenericSprite(pos, surface, groups, owner, z), moving(moving)
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
        rect.pos += direction * speed * deltaTime;
    }

    const double current_time = rl::GetTime();
    if (current_time - start_time >= lifetime / 1000.0f)
    {
        const auto drop = Kill();
        delete drop;
    }
}
