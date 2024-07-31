#pragma once
#include <rygame.h>
#include "Player.h"


class CameraGroup : public rg::sprite::Group
{
public:

    CameraGroup() = default;

    void CustomDraw(const Player *player);

private:

    rg::Surface *display_surface = rg::display::GetSurface();
    rg::math::Vector2 offset{};
};
