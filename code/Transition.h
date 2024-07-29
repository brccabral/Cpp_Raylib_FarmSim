#pragma once
#include "Player.h"


class Transition
{
public:

    Transition(const std::function<void()> &reset, Player *player);
    ~Transition();

    void Play();

private:

    rg::Surface *display_surface = nullptr;

    std::function<void()> reset = nullptr;
    Player *player = nullptr;

    rg::Surface *image = nullptr;
    int color = 255;
    int speed = -5; // fade to black speed = -2
};
