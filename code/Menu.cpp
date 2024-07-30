#include "Menu.h"

Menu::Menu(Player *player, const std::function<void()> &toggle_menu)
    : player(player), toggle_menu(toggle_menu)
{
    auto s = rg::getKeys<std::string, decltype(player->seed_inventory)>(player->seed_inventory);
    options = rg::getKeys<std::string, decltype(player->item_inventory)>(player->item_inventory);
    options.insert(options.end(), s.begin(), s.end());
    sell_border = player->item_inventory.size() - 1;
    Setup();
}

Menu::~Menu()
{
    for (const auto *text_surf: text_surfs)
    {
        delete text_surf;
    }
}

void Menu::Update()
{
    Input();
    for (int text_index = 0; text_index < text_surfs.size(); ++text_index)
    {
        display_surface->Blit(text_surfs[text_index], {100.0f, text_index * 50.0f});
    }
}

void Menu::Input()
{
    if (IsKeyReleased(rl::KEY_ESCAPE))
    {
        toggle_menu();
    }
}

void Menu::Setup()
{
    for (auto &item: options)
    {
        auto *text_surf = font.render(item.c_str(), rl::BLACK);
        text_surfs.emplace_back(text_surf);
    }
}
