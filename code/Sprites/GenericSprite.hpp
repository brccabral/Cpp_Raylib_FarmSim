#pragma once
#include <rygame.hpp>
#include "../Settings.hpp"


class GenericSprite : public rg::sprite::Sprite
{
public:

    GenericSprite(
            rg::math::Vector2 pos, rg::Surface *surf,
            unsigned int z = LAYERS["main"]);
    void InitImage(rg::Surface *surf);

    rg::Rect hitbox{};
};
