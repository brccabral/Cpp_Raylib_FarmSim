#pragma once
#include <raylib_utils.h>
#include "../Settings.h"


class GenericSprite : public rg::sprite::SimpleSprite
{
public:

    GenericSprite(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::SpriteGroup *> &groups,
            unsigned int z = LAYERS["main"]);

    rg::RectangleU hitbox{};
};
