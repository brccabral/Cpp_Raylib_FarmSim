#pragma once
#include <rygame.h>
#include "../Settings.h"


class GenericSprite : public rg::sprite::Sprite
{
public:

    GenericSprite(
            rg::math::Vector2 pos, rg::Surface *surf,
            const std::vector<rg::sprite::Group *> &groups, unsigned int z = LAYERS["main"]);

    rg::Rect hitbox{};
};
