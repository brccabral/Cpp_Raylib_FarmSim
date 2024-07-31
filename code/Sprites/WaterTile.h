#pragma once
#include <rygame.h>


class WaterTile : rg::sprite::Sprite
{
public:

    WaterTile(
            rg::math::Vector2 pos, rg::Surface *surface, const std::vector<rg::sprite::Group *> &groups);
    ~WaterTile() override;
};
