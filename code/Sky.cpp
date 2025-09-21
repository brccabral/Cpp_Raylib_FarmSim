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

    if (current_color != start_color)
    {
        current_color = rg::math::Vector3uc{start_color};
        full_surf.Fill(
                {current_color.r, current_color.g, current_color.b, 255});
    }
    display_surface->Blit(&full_surf, rg::math::Vector2{}, rl::BLEND_MULTIPLIED);
}
