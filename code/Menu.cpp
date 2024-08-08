#include "Menu.h"

#include "Settings.h"

Menu::Menu(const std::shared_ptr<Player> &player, const std::function<void()> &toggle_menu)
    : player(player), toggle_menu(toggle_menu)
{
    auto s = rg::getKeys<std::string, decltype(player->seed_inventory)>(player->seed_inventory);
    options = rg::getKeys<std::string, decltype(player->item_inventory)>(player->item_inventory);
    options.insert(options.end(), s.begin(), s.end());
    sell_border = player->item_inventory.size() - 1;
    Setup();
}

void Menu::Update()
{
    timer.Update();
    Input();
    DisplayMoney();
    auto s = rg::getValues<unsigned int, decltype(player->seed_inventory)>(player->seed_inventory);
    auto amount_list =
            rg::getValues<unsigned int, decltype(player->item_inventory)>(player->item_inventory);
    amount_list.insert(amount_list.end(), s.begin(), s.end());

    for (int text_index = 0; text_index < text_surfs.size(); ++text_index)
    {
        const float top = main_rect.top() + text_index * (text_surfs[text_index]->GetRect().height +
                                                          (padding * 2) + space);
        ShowEntry(text_surfs[text_index], amount_list[text_index], top, index == text_index);
    }
}

void Menu::Input()
{
    if (IsKeyReleased(rl::KEY_ESCAPE))
    {
        toggle_menu();
    }

    // the timer is not needed in here because we are using IsKeyReleased, but it is here to be
    // compliant with the tutorial
    if (!timer.active)
    {
        if (IsKeyReleased(rl::KEY_UP))
        {
            --index;
            timer.Activate();
        }
        if (IsKeyReleased(rl::KEY_DOWN))
        {
            ++index;
            timer.Activate();
        }
        if (IsKeyReleased(rl::KEY_SPACE))
        {
            timer.Activate();
            // get item
            const auto &current_item = options[index];
            // sell/buy
            if (index <= sell_border)
            {
                if (player->item_inventory[current_item] > 0)
                {
                    --player->item_inventory[current_item];
                    player->money += SALE_PRICES[current_item];
                }
            }
            else
            {
                const auto seed_price = PURCHASE_PRICES[current_item];
                if (player->money >= seed_price)
                {
                    ++player->seed_inventory[current_item];
                    player->money -= seed_price;
                }
            }
        }
    }
    // clamp the values
    // circular list
    if (index < 0)
    {
        index = options.size() - 1;
    }
    else if (index > options.size() - 1)
    {
        index = 0;
    }
}

void Menu::Setup()
{
    for (auto &item: options)
    {
        auto text_surf = font.render(item.c_str(), rl::BLACK);
        text_surfs.emplace_back(text_surf);
        total_height += text_surf->GetRect().height + (padding * 2);
    }
    total_height += (text_surfs.size() - 1) * space;
    menu_top = SCREEN_HEIGHT / 2.0f - total_height / 2.0f;
    main_rect = {(SCREEN_WIDTH / 2.0f - width / 2.0f), menu_top, width, total_height};

    // buy or sell
    buy_text = font.render("buy", rl::BLACK);
    sell_text = font.render("sell", rl::BLACK);
}

void Menu::DisplayMoney() const
{
    const auto text_surf =
            font.render(rl::TextFormat("$%s", std::to_string(player->money).c_str()), rl::BLACK);
    const rg::Rect text_rect =
            text_surf->GetRect().midbottom({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 20});

    rg::draw::rect(*display_surface, rl::WHITE, text_rect.inflate(10, 10), 0, 4);
    display_surface->Blit(text_surf, text_rect.pos);
}

void Menu::ShowEntry(
        const std::shared_ptr<rg::Surface> &text_surf, const unsigned int amount, const float top,
        const bool selected) const
{
    // background
    const rg::Rect bg_rect = {
            main_rect.left(), top, width, text_surf->GetRect().height + padding * 2};
    rg::draw::rect(*display_surface, rl::WHITE, bg_rect, 0, 4);

    // text
    rg::Rect text_rect = text_surf->GetRect();
    text_rect.midleft({main_rect.left() + 20, bg_rect.centery()});
    display_surface->Blit(text_surf, text_rect.pos);

    // amount
    auto amount_surf = font.render(std::to_string(amount).c_str(), rl::BLACK);
    rg::Rect amount_rect = amount_surf->GetRect();
    amount_rect.midright({main_rect.right() - 20, bg_rect.centery()});
    display_surface->Blit(amount_surf, amount_rect.pos);

    // selected
    if (selected)
    {
        rg::draw::rect(*display_surface, rl::BLACK, bg_rect, 4, 4);
        if (index <= sell_border)
        {
            rg::Rect pos_rect = sell_text->GetRect();
            pos_rect.midleft({main_rect.left() + 150.0f, bg_rect.centery()});
            display_surface->Blit(sell_text, pos_rect.pos);
        }
        else
        {
            rg::Rect pos_rect = buy_text->GetRect();
            pos_rect.midleft({main_rect.left() + 150.0f, bg_rect.centery()});
            display_surface->Blit(buy_text, pos_rect.pos);
        }
    }
}
