#pragma once
#include <raylib_utils.h>


class SoilTile : public rg::sprite::Sprite
{
public:

    SoilTile(rl::Vector2 pos, rg::Surface *surface, const std::vector<rg::sprite::Group *> &groups);
    ~SoilTile() override;
};
