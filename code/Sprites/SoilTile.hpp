#pragma once
#include <rygame.hpp>


class SoilTile : public rg::sprite::Sprite
{
public:

    SoilTile(rg::math::Vector2 pos, rg::Surface *surface);
    ~SoilTile() override;
};
