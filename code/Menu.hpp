#pragma once
#include "Player.hpp"

class Menu
{
public:

    Menu() = default;
    Menu(Player *player, const std::function<void()> &toggle_menu);
    Menu(const Menu &other) = delete;
    Menu &operator=(const Menu &other) = delete;
    Menu(Menu &&other) = default;
    Menu &operator=(Menu &&other) = default;

    void Update();
    void Input();

private:

    void Setup();
    void DisplayMoney();
    void ShowEntry(rg::Surface *entry_surf, rg::Surface *amount_surf, float top, bool selected);

    Player *player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    rg::Surface *display_surface = &rg::display::GetSurface();
    rg::font::Font font{};

    // options
    float width = 400;
    float space = 10;
    float padding = 8;

    // entries
    std::vector<std::string> options{};
    int sell_border = 0;

    std::vector<rg::Surface> entries_surfs{};
    std::vector<rg::Surface> amount_surfs{};
    std::vector<std::string> amount_text{};
    float total_height{};
    float menu_top{};
    rg::Rect main_rect{};

    // movement
    int index = 0;
    rg::Timer timer = rg::Timer(0.2f);

    // buy or sell text surface
    rg::Surface buy_text{};
    rg::Surface sell_text{};

    rg::Surface money_surface{};
};
