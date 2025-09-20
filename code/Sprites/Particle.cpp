#include <iostream>
#include "Particle.hpp"

Particle::Particle(
        const rg::math::Vector2 pos, rg::Surface *surf, const unsigned int z,
        const double duration)
    : GenericSprite(pos, surf, z), is_alive(true), duration(duration)
{
    start_time = rl::GetTime();

    // the passed surf is going to be used as mask and replaced with a new surface
    // we don't need to delete the passed surf here, but in the class that creates the particle
    const auto mask_surf = rg::mask::FromSurface(surf);
    mask = mask_surf.ToSurface();
    mask.SetColorKey(rl::BLACK);
    image = &mask;
}

void Particle::Update(float deltaTime)
{
    const double current_time = rl::GetTime();
    if (current_time - start_time > duration)
    {
        Kill();
        is_alive = false;
    }
}
