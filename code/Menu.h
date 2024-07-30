#pragma once
#include "Player.h"

class Menu
{
public:

    Menu(Player *player, const std::function<void()> &toggle_menu);
    ~Menu();
    void Update();
    void Input() const;

private:

    void Setup();
    void DisplayMoney() const;
    void ShowEntry(rg::Surface *text_surf, unsigned int amount, float top);

    Player *player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    rg::Surface *display_surface = rg::display::GetSurface();
    rg::font::Font font = rg::font::Font("resources/font/LycheeSoda.ttf", 30);

    // options
    float width = 400;
    float space = 10;
    float padding = 8;

    // entries
    std::vector<std::string> options;
    unsigned int sell_border = 0;

    std::vector<rg::Surface *> text_surfs;
    float total_height{};
    float menu_top{};
    rg::Rect main_rect{};
};
