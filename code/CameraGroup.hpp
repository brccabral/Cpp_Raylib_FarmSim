#pragma once
#include <rygame.hpp>
#include "Player.hpp"


class CameraGroup : public rg::sprite::Group
{
public:

    CameraGroup() = default;

    void CustomDraw(const Player *player);

private:

    rg::Surface *display_surface = &rg::display::GetSurface();
    rg::math::Vector2 offset{};
};
