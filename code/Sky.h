#pragma once
#include <rygame.h>


class Sky
{
public:

    Sky();
    void Display(float dt);
    rl::Vector3 start_color{};

private:

    rg::Surface *display_surface = nullptr;
    rg::Surface *full_surf = nullptr;
    rl::Vector3 end_color{};
};
