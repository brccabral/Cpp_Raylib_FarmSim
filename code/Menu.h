#pragma once
#include "Player.h"

class Menu
{
public:

    Menu(const std::shared_ptr<Player> &player, const std::function<void()> &toggle_menu);
    void Update();
    void Input();

private:

    void Setup();
    void DisplayMoney() const;
    void ShowEntry(
            const std::shared_ptr<rg::Surface> &text_surf, unsigned int amount, float top,
            bool selected) const;

    std::shared_ptr<Player> player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    std::shared_ptr<rg::Surface> display_surface = rg::display::GetSurface();
    rg::font::Font font = rg::font::Font("resources/font/LycheeSoda.ttf", 30);

    // options
    float width = 400;
    float space = 10;
    float padding = 8;

    // entries
    std::vector<std::string> options;
    unsigned int sell_border = 0;

    std::vector<std::shared_ptr<rg::Surface>> text_surfs{};
    float total_height{};
    float menu_top{};
    rg::Rect main_rect{};

    // movement
    int index = 0;
    rg::Timer timer = rg::Timer(0.2f);

    // buy or sell text surface
    std::shared_ptr<rg::Surface> buy_text = nullptr;
    std::shared_ptr<rg::Surface> sell_text = nullptr;
};
