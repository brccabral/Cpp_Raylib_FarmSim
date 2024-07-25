#include "Particle.h"

Particle::Particle(
        const rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups, const unsigned int z,
        const float duration)
    : GenericSprite(pos, surf, groups, z), duration(duration)
{
    start_time = rl::GetFrameTime();

    // the passed surf is the apple image
    // it is assigned to `this->image` in GenericSprite
    // we don't need to delete it because it will be deleted with the apple
    const auto mask_surf = rg::mask::FromSurface(image);
    const auto new_surf = mask_surf.ToSurface();
    image = new_surf;
}

void Particle::Update(float deltaTime)
{
    const float current_time = rl::GetFrameTime();
    if (current_time - start_time > duration)
    {
        Kill();
    }
}
