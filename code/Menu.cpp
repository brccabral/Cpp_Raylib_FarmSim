#include "Menu.h"

#include "Settings.h"

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
    rg::draw::rect(display_surface, rl::RED, main_rect);
    DisplayMoney();
    for (int text_index = 0; text_index < text_surfs.size(); ++text_index)
    {
        const float top = main_rect.y + text_index * (text_surfs[text_index]->GetRect().height +
                                                      (padding * 2) + space);
        ShowEntry(text_surfs[text_index], 0, top);
        display_surface->Blit(text_surfs[text_index], {100.0f, text_index * 50.0f});
    }
}

void Menu::Input() const
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
        total_height += text_surf->GetRect().height + (padding * 2);
    }
    total_height += (text_surfs.size() - 1) * space;
    menu_top = SCREEN_HEIGHT / 2.0f - total_height / 2.0f;
    main_rect = {(SCREEN_WIDTH / 2.0f - width / 2.0f), menu_top, width, total_height};
}

void Menu::DisplayMoney() const
{
    auto *text_surf =
            font.render(rl::TextFormat("$%s", std::to_string(player->money).c_str()), rl::BLACK);
    rg::RectangleU text_rect = text_surf->GetRect();
    RectToMidBottom(text_rect, {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 20});

    rg::draw::rect(display_surface, rl::WHITE, GetRectInflate(text_rect, 10, 10), 0, 4);
    display_surface->Blit(text_surf, text_rect.pos);
}

void Menu::ShowEntry(const rg::Surface *text_surf, unsigned int amount, const float top)
{
    // background
    const rg::RectangleU bg_rect = {
            main_rect.x, top, width, text_surf->GetRect().height + padding * 2};
    rg::draw::rect(display_surface, rl::WHITE, bg_rect, 0, 4);
}
