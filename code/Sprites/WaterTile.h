#pragma once
#include <raylib_utils.h>


class WaterTile : rg::sprite::Sprite
{
public:

    WaterTile(
            rl::Vector2 pos, rg::Surface *surface, const std::vector<rg::sprite::Group *> &groups);
    ~WaterTile() override;
};
