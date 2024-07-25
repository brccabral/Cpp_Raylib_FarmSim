#pragma once
#include <raylib_utils.h>
#include "Player.h"


class CameraGroup : public rg::sprite::SpriteGroup
{
public:

    CameraGroup();

    void CustomDraw(const Player *player);

private:

    rg::Surface *display_surface = nullptr;
    rl::Vector2 offset{};
};
