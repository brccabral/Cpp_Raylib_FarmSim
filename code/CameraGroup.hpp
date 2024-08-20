#pragma once
#include <rygame.hpp>
#include "Player.hpp"


class CameraGroup : public rg::sprite::Group
{
public:

    CameraGroup() = default;

    void CustomDraw(const std::shared_ptr<Player> &player);

private:

    std::shared_ptr<rg::Surface> display_surface = rg::display::GetSurface();
    rg::math::Vector2 offset{};
};
