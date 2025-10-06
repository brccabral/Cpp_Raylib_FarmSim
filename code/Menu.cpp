#include "Menu.hpp"

#include "Settings.hpp"

Menu::Menu(Player *player, const std::function<void()> &toggle_menu)
    : player(player), toggle_menu(toggle_menu),
      font(rg::font::Font("resources/font/LycheeSoda.ttf", 30))
{
    options.reserve(player->item_inventory.size() + player->seed_inventory.size());
    for (auto &item_name: player->item_inventory | std::views::keys)
    {
        options.push_back(item_name);
    }
    for (auto &seed_name: player->seed_inventory | std::views::keys)
    {
        options.push_back(seed_name);
    }

    sell_border = player->item_inventory.size() - 1;
    Setup();
}

void Menu::Update()
{
    timer.Update();
    Input();
    DisplayMoney();
    std::vector<unsigned int> amount_list;
    for (auto item: player->item_inventory | std::views::values)
    {
        amount_list.emplace_back(item);
    }
    for (auto seed: player->seed_inventory | std::views::values)
    {
        amount_list.emplace_back(seed);
    }

    for (unsigned int text_index = 0; text_index < entries_surfs.size(); ++text_index)
    {
        const float top = main_rect.top() + text_index * (
                              entries_surfs[text_index].GetRect().height +
                              padding * 2 + space);
        amount_text[text_index] = std::to_string(amount_list[text_index]);
        amount_surfs[text_index] = font.render(amount_text[text_index].c_str(), rl::BLACK);
        ShowEntry(
                &entries_surfs[text_index], &amount_surfs[text_index], top,
                index == static_cast<int>(text_index));
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
        // clamp the values
        // circular list
        if (index < 0)
        {
            index = options.size() - 1;
        }
        else if (index > (int) options.size() - 1)
        {
            index = 0;
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
                    player->money += Settings::GetInstance().SALE_PRICES[current_item];
                }
            }
            else
            {
                const auto seed_price = Settings::GetInstance().PURCHASE_PRICES[current_item];
                if (player->money >= seed_price)
                {
                    ++player->seed_inventory[current_item];
                    player->money -= seed_price;
                }
            }
        }
    }
}

void Menu::Setup()
{
    for (auto &item: options)
    {
        auto entry_surf = font.render(item.c_str(), rl::BLACK);
        total_height += entry_surf.GetRect().height + padding * 2;
        entries_surfs.push_back(std::move(entry_surf));
        amount_text.emplace_back("0");
        auto amount_surf = font.render(amount_text.back().c_str(), rl::BLACK);
        amount_surfs.push_back(std::move(amount_surf));
    }
    total_height += (entries_surfs.size() - 1) * space;
    menu_top = SCREEN_HEIGHT / 2.0f - total_height / 2.0f;
    main_rect = {(SCREEN_WIDTH / 2.0f - width / 2.0f), menu_top, width, total_height};

    // buy or sell
    buy_text = font.render("buy", rl::BLACK);
    sell_text = font.render("sell", rl::BLACK);
}

void Menu::DisplayMoney()
{
    money_surface =
            font.render(rl::TextFormat("$%s", std::to_string(player->money).c_str()), rl::BLACK);
    const rg::Rect text_rect =
            money_surface.GetRect().midbottom({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 20.0f});

    rg::draw::rect(display_surface, rl::WHITE, text_rect.inflate(10, 10), 0, 4);
    display_surface->Blit(&money_surface, text_rect);
}

void Menu::ShowEntry(
        rg::Surface *entry_surf, rg::Surface *amount_surf, const float top, const bool selected)
{
    // background
    const rg::Rect bg_rect = {
            main_rect.left(), top, width, entry_surf->GetRect().height + padding * 2};
    rg::draw::rect(display_surface, rl::WHITE, bg_rect, 0, 4);

    // text
    rg::Rect text_rect = entry_surf->GetRect();
    text_rect.midleft({main_rect.left() + 20, bg_rect.centery()});
    display_surface->Blit(entry_surf, text_rect);

    // amount
    rg::Rect amount_rect = amount_surf->GetRect();
    amount_rect.midright({main_rect.right() - 20, bg_rect.centery()});
    display_surface->Blit(amount_surf, amount_rect);

    // selected
    if (selected)
    {
        rg::draw::rect(display_surface, rl::BLACK, bg_rect, 4, 4);
        if (index <= sell_border)
        {
            rg::Rect pos_rect = sell_text.GetRect();
            pos_rect.midleft({main_rect.left() + 150.0f, bg_rect.centery()});
            display_surface->Blit(&sell_text, pos_rect);
        }
        else
        {
            rg::Rect pos_rect = buy_text.GetRect();
            pos_rect.midleft({main_rect.left() + 150.0f, bg_rect.centery()});
            display_surface->Blit(&buy_text, pos_rect);
        }
    }
}
