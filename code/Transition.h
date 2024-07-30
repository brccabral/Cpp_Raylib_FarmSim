#pragma once
#include "Player.h"
#include "Settings.h"


class Transition
{
public:

    Transition(const std::function<void()> &reset, Player *player);
    ~Transition();

    void Play();

private:

    rg::Surface *display_surface = rg::display::GetSurface();

    std::function<void()> reset = nullptr;
    Player *player = nullptr;

    rg::Surface *image = new rg::Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
    int color = 255;
    int speed = -5; // fade to black speed = -2
};
