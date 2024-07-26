#include "Drop.h"

Drop::Drop(
        const rl::Vector2 pos, rg::Surface *surface, const std::vector<rg::sprite::Group *> &groups,
        const unsigned int z, bool moving)
    : GenericSprite(pos, surface, groups, z), moving(moving)
{
    lifetime = rl::GetRandomValue(400, 500);
    start_time = rl::GetTime();

    if (moving)
    {
        direction = {-2, 4};
        speed = rl::GetRandomValue(200, 250);
    }
}

Drop::~Drop()
{
    // this image is created and destroyed in Rain()
    image = nullptr;
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
        Kill();
    }
}
