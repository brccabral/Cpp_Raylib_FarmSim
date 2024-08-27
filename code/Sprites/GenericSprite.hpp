#pragma once
#include <rygame.hpp>
#include "../Settings.hpp"


class GenericSprite : public rg::sprite::Sprite
{
public:

    GenericSprite(
            rg::math::Vector2 pos, const rg::Surface_Ptr &surf,
            unsigned int z = LAYERS["main"]);
    void InitImage(const rg::Surface_Ptr &surf);

    rg::Rect hitbox{};
};
