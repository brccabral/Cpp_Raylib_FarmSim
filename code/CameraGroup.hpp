#pragma once
#include <rygame.hpp>
#include "Player.hpp"


class CameraGroup : public rg::sprite::Group
{
public:

    CameraGroup() = default;

    void CustomDraw(const std::shared_ptr<Player> &player);

private:

    rg::Surface_Ptr display_surface = rg::display::GetSurface();
    rg::math::Vector2 offset{};
};
