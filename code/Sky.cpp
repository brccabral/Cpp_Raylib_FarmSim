#include "Sky.h"
#include "Settings.h"

Sky::Sky()
{
    display_surface = rg::display::GetSurface();
    full_surf = new rg::Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
    start_color = {255, 255, 255};
    end_color = {38, 101, 189};
}

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

    full_surf->Fill(
            {(unsigned char) start_color.x, (unsigned char) start_color.y,
             (unsigned char) start_color.z, 255});
    display_surface->Blit(full_surf, {}, rl::BLEND_MULTIPLIED);
}
