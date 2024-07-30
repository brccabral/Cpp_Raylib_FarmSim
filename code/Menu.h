#pragma once
#include "Player.h"

class Menu
{
public:

    Menu(Player *player, const std::function<void()> &toggle_menu);
    void Update();
    void Input();

private:

    Player *player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    rg::Surface *display_surface = rg::display::GetSurface();
    rl::Font font = rl::LoadFontEx("resources/font/LycheeSoda.ttf", 30, nullptr, 0);
};
