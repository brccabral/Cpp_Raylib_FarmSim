#include "Menu.h"

Menu::Menu(Player *player, const std::function<void()> &toggle_menu)
    : player(player), toggle_menu(toggle_menu)
{
    auto s = rg::getKeys(player->seed_inventory);
    options = rg::getKeys(player->item_inventory);
    options.insert(options.begin(), s.begin(), s.end());
    sell_border = player->item_inventory.size() - 1;
    Setup();
}

void Menu::Update()
{
    rg::Surface surface{1000, 1000};
    surface.Fill(rl::BLACK);
    display_surface->Blit(&surface);
}

void Menu::Input()
{
    if (IsKeyReleased(rl::KEY_ESCAPE))
    {
        toggle_menu();
    }
}

void Menu::Setup()
{}
