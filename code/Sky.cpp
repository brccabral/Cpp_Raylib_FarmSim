#include "Sky.hpp"


void Sky::Display(const float dt)
{
    if (start_color.x > end_color.x)
    {
        start_color.x -= 2 * dt;
    }
    if (start_color.y > end_color.y)
    {
        start_color.y -= 2 * dt;
    }
    if (start_color.z > end_color.z)
    {
        start_color.z -= 2 * dt;
    }

    full_surf.Fill(
    {(unsigned char) start_color.x, (unsigned char) start_color.y,
     (unsigned char) start_color.z, 255});
    display_surface->Blit(&full_surf, rg::math::Vector2{}, rl::BLEND_MULTIPLIED);
}
