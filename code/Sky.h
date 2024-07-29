#pragma once
#include <rygame.h>


class Sky
{
public:

    Sky();
    void Display(float dt);

private:

    rg::Surface *display_surface = nullptr;
    rg::Surface *full_surf = nullptr;
    rl::Color start_color{};
};
