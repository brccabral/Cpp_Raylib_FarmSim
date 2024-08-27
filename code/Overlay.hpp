#pragma once
#include "Player.hpp"


class Overlay
{
public:

    explicit Overlay(const std::shared_ptr<Player> &player);
    void Display();

private:

    rg::Surface_Ptr display_surface = rg::display::GetSurface();
    std::shared_ptr<Player> player;

    std::map<std::string, rg::Surface_Ptr> tools_surfaces{};
    std::map<std::string, rg::Surface_Ptr> seeds_surfaces{};
};
