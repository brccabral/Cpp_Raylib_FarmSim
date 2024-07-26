#include "Particle.h"

Particle::Particle(
        const rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups, const unsigned int z,
        const double duration)
    : GenericSprite(pos, surf, groups, z), duration(duration)
{
    start_time = rl::GetTime();

    // the passed surf is the apple image
    // it is assigned to `this->image` in GenericSprite
    // we don't need to delete it because it will be deleted with the apple
    const auto mask_surf = rg::mask::FromSurface(image);
    const auto new_surf = mask_surf.ToSurface();
    new_surf->SetColorKey(rl::BLACK);
    image = new_surf;
}

void Particle::Update(float deltaTime)
{
    const double current_time = rl::GetTime();
    if (current_time - start_time > duration)
    {
        Kill();
    }
}
