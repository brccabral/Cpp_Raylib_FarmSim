#pragma once
#include "Settings.h"
#include <rygame.h>


class Sky
{
public:

    Sky() = default;
    void Display(float dt);
    rl::Vector3 start_color{255, 255, 255};

private:

    rg::Surface *display_surface = rg::display::GetSurface();
    rg::Surface *full_surf = new rg::Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
    rl::Vector3 end_color{38, 101, 189};
};
