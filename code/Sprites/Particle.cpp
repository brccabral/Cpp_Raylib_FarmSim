#include "Particle.hpp"

Particle::Particle(
        const rg::math::Vector2<float> pos, rg::Surface *surf, const unsigned int z,
        const double duration)
    : GenericSprite(pos, surf, z), is_alive(true), duration(duration)
{
    start_time = rl::GetTime();

    // the passed surf is going to be used as mask and replaced with a new surface
    // we don't need to delete the passed surf here, but in the class that creates the particle
    const auto mask = rg::mask::FromSurface(surf);
    mask_surface = mask.ToSurface();
    mask_surface.SetColorKey(rl::BLACK);
    image = &mask_surface;
}

Particle::Particle(Particle &&other) noexcept
    : Particle()
{
    *this = std::move(other);
}

Particle &Particle::operator=(Particle &&other) noexcept
{
    if (this != &other)
    {
        is_alive = other.is_alive;
        start_time = other.start_time;
        duration = other.duration;
        mask_surface = std::move(other.mask_surface);
        GenericSprite::operator=(std::move(other));

        image = &mask_surface;
    }
    return *this;
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
