#pragma once
#include "Player.h"

class Menu
{
public:

    Menu(Player *player, const std::function<void()> &toggle_menu);
    ~Menu();
    void Update();
    void Input();

private:

    void Setup();
    void DisplayMoney();

    Player *player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    rg::Surface *display_surface = rg::display::GetSurface();
    rg::font::Font font = rg::font::Font("resources/font/LycheeSoda.ttf", 30);

    // options
    unsigned int width = 400;
    unsigned int space = 10;
    unsigned int padding = 8;

    // entries
    std::vector<std::string> options;
    unsigned int sell_border = 0;

    std::vector<rg::Surface *> text_surfs;
    unsigned int total_height{};
    unsigned int menu_top{};
    rg::RectangleU main_rect{};
};
