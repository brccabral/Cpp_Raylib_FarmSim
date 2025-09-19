#pragma once
#include "Player.hpp"
#include "Settings.hpp"


class Transition
{
public:

    Transition() = default;
    Transition(const std::function<void()> &reset, Player *player);

    void Play();

private:

    rg::Surface *display_surface = &rg::display::GetSurface();

    std::function<void()> reset = nullptr;
    Player *player = nullptr;

    rg::Surface image = rg::Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
    int color = 255;
    int speed = -5; // fade to black speed = -2
};
