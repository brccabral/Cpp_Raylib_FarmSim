#pragma once
#include "Player.hpp"


class Overlay
{
public:

    Overlay() = default;
    explicit Overlay(Player *player);
    void Display();

private:

    rg::Surface *display_surface = &rg::display::GetSurface();
    Player *player = nullptr;

    std::map<std::string, rg::Surface> tools_surfaces{};
    std::map<std::string, rg::Surface> seeds_surfaces{};
};
