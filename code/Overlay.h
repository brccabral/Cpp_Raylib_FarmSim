#pragma once
#include "Player.h"


class Overlay
{
public:

    explicit Overlay(Player *player);
    ~Overlay();
    void Display();

private:

    Player *player;

    std::map<std::string, Surface *> tools_surfaces;
    std::map<std::string, Surface *> seeds_surfaces;
};
