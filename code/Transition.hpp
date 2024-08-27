#pragma once
#include "Player.hpp"
#include "Settings.hpp"


class Transition
{
public:

    Transition(const std::function<void()> &reset, const std::shared_ptr<Player> &player);

    void Play();

private:

    rg::Surface_Ptr display_surface = rg::display::GetSurface();

    std::function<void()> reset = nullptr;
    std::shared_ptr<Player> player = nullptr;

    rg::Surface_Ptr image = std::make_shared<rg::Surface>(SCREEN_WIDTH, SCREEN_HEIGHT);
    int color = 255;
    int speed = -5; // fade to black speed = -2
};
