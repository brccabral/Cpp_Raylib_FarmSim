#pragma once
#include <rygame.hpp>


class WaterTile : public rg::sprite::Sprite
{
public:

    WaterTile(rg::math::Vector2 pos, const rg::Surface_Ptr &surface);
    ~WaterTile() override;
};
