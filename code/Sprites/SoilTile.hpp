#pragma once
#include <rygame.hpp>


class SoilTile : public rg::sprite::Sprite
{
public:

    SoilTile() = default;
    SoilTile(rg::math::Vector2<float> pos, rg::Surface *surface);
};
