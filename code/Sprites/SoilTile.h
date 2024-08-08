#pragma once
#include <rygame.h>


class SoilTile : public rg::sprite::Sprite
{
public:

    SoilTile(rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surface);
    ~SoilTile() override;
};
