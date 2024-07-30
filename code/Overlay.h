#pragma once
#include "Player.h"


class Overlay
{
public:

    explicit Overlay(Player *player);
    ~Overlay();
    void Display();

private:

    rg::Surface *display_surface = rg::display::GetSurface();
    Player *player;

    std::map<std::string, rg::Surface *> tools_surfaces;
    std::map<std::string, rg::Surface *> seeds_surfaces;
};
