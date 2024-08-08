#pragma once
#include <rygame.h>


class SoilTile : public rg::sprite::Sprite
{
public:

    SoilTile(
            rg::math::Vector2 pos, rg::Surface *surface,
            const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner);
    ~SoilTile() override;
};
