#include "Sky.h"
#include "Settings.h"

Sky::Sky()
{
    display_surface = rg::display::GetSurface();
    full_surf = new rg::Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
    start_color = {255, 255, 255, 255};
}

void Sky::Display(float dt)
{
    full_surf->Fill(start_color);
    display_surface->Blit(full_surf, {}, rl::BLEND_MULTIPLIED);
}
