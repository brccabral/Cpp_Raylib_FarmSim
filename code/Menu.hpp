#pragma once
#include "Player.hpp"

class Menu
{
public:

    Menu() = default;
    Menu(Player *player, const std::function<void()> &toggle_menu);
    void Update();
    void Input();

private:

    void Setup();
    void DisplayMoney();
    void ShowEntry(
            const rg::Surface *text_surf, unsigned int amount, float top,
            bool selected);

    Player *player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    rg::Surface *display_surface = &rg::display::GetSurface();
    rg::font::Font font = rg::font::Font("resources/font/LycheeSoda.ttf", 30);

    // options
    float width = 400;
    float space = 10;
    float padding = 8;

    // entries
    std::vector<std::string> options{};
    int sell_border = 0;

    std::vector<rg::Surface> text_surfs{};
    float total_height{};
    float menu_top{};
    rg::Rect main_rect{};

    // movement
    int index = 0;
    rg::Timer timer = rg::Timer(0.2f);

    // buy or sell text surface
    rg::Surface buy_text{};
    rg::Surface sell_text{};
};
