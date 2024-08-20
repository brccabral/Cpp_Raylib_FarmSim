#pragma once
#include <rygame.hpp>


class WaterTile : public rg::sprite::Sprite
{
public:

    WaterTile(rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surface);
    ~WaterTile() override;
};
