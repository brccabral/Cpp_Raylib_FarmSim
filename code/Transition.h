#pragma once
#include "Player.h"
#include "Settings.h"


class Transition
{
public:

    Transition(const std::function<void()> &reset, Player *player);

    void Play();

private:

    rg::Surface *display_surface = rg::display::GetSurface();

    std::function<void()> reset = nullptr;
    Player *player = nullptr;

    rg::Surface *image = rg::Surface::Create(SCREEN_WIDTH, SCREEN_HEIGHT);
    int color = 255;
    int speed = -5; // fade to black speed = -2
};
