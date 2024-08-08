#pragma once
#include "Player.h"


class Overlay
{
public:

    explicit Overlay(const std::shared_ptr<Player> &player);
    void Display();

private:

    std::shared_ptr<rg::Surface> display_surface = rg::display::GetSurface();
    std::shared_ptr<Player> player;

    std::map<std::string, std::shared_ptr<rg::Surface>> tools_surfaces{};
    std::map<std::string, std::shared_ptr<rg::Surface>> seeds_surfaces{};
};
