#pragma once
#include <rygame.hpp>


class WaterTile : public rg::sprite::Sprite
{
public:

    WaterTile() = default;
    WaterTile(rg::math::Vector2<float> pos, rg::Surface *surface);
};
