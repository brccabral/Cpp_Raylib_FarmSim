#pragma once
#include "Player.hpp"

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
            const rg::Surface_Ptr &text_surf, unsigned int amount, float top,
            bool selected) const;

    std::shared_ptr<Player> player = nullptr;
    std::function<void()> toggle_menu = nullptr;
    rg::Surface_Ptr display_surface = rg::display::GetSurface();
    rg::font::Font font = rg::font::Font("resources/font/LycheeSoda.ttf", 30);

    // options
    float width = 400;
    float space = 10;
    float padding = 8;

    // entries
    std::vector<std::string> options;
    int sell_border = 0;

    std::vector<rg::Surface_Ptr> text_surfs{};
    float total_height{};
    float menu_top{};
    rg::Rect main_rect{};

    // movement
    int index = 0;
    rg::Timer timer = rg::Timer(0.2f);

    // buy or sell text surface
    rg::Surface_Ptr buy_text = nullptr;
    rg::Surface_Ptr sell_text = nullptr;
};
