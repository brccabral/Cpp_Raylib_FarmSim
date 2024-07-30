#include "Menu.h"

Menu::Menu(Player *player, const std::function<void()> &toggle_menu)
    : player(player), toggle_menu(toggle_menu)
{}

void Menu::Update()
{
    rg::Surface surface{1000, 1000};
    surface.Fill(rl::BLACK);
    display_surface->Blit(&surface);
}
