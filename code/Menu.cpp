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
    DisplayMoney();
    for (int text_index = 0; text_index < text_surfs.size(); ++text_index)
    {
        const float top = main_rect.y + text_index * (text_surfs[text_index]->GetRect().height +
                                                      (padding * 2) + space);
        ShowEntry(text_surfs[text_index], 0, top);
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
    rg::Rect text_rect = text_surf->GetRect();
    text_rect.midbottom({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 20});

    rg::draw::rect(display_surface, rl::WHITE, text_rect.inflate(10, 10), 0, 4);
    display_surface->Blit(text_surf, text_rect.pos);
    delete text_surf;
}

void Menu::ShowEntry(rg::Surface *text_surf, const unsigned int amount, const float top)
{
    // background
    const rg::Rect bg_rect = {
            main_rect.left(), top, width, text_surf->GetRect().height + padding * 2};
    rg::draw::rect(display_surface, rl::WHITE, bg_rect, 0, 4);

    // text
    rg::Rect text_rect = text_surf->GetRect();
    text_rect.midleft({main_rect.left() + 20, bg_rect.centery()});
    display_surface->Blit(text_surf, text_rect.pos);

    // amount
    rg::Surface *amount_surf = font.render(std::to_string(amount).c_str(), rl::BLACK);
    rg::Rect amount_rect = amount_surf->GetRect();
    amount_rect.midright({main_rect.right() - 20, bg_rect.centery()});
    display_surface->Blit(amount_surf, amount_rect.pos);
}
