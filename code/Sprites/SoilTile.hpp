#pragma once
#include <rygame.hpp>


class SoilTile : public rg::sprite::Sprite
{
public:

    SoilTile(rg::math::Vector2 pos, const rg::Surface_Ptr &surface);
    ~SoilTile() override;
};
