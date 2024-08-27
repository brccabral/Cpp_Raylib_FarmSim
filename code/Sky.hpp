#pragma once
#include "Settings.hpp"
#include <rygame.hpp>


class Sky
{
public:

    Sky() = default;
    void Display(float dt);
    rl::Vector3 start_color{255, 255, 255};

private:

    rg::Surface_Ptr display_surface = rg::display::GetSurface();
    rg::Surface_Ptr full_surf =
            std::make_shared<rg::Surface>(SCREEN_WIDTH, SCREEN_HEIGHT);
    rl::Vector3 end_color{38, 101, 189};
};
