#pragma once
#include <raylib_utils.h>
#include "../Settings.h"


class GenericSprite : public rg::SimpleSprite
{
public:

    GenericSprite(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::SpriteGroup *> &groups,
            unsigned int z = LAYERS["main"]);

    rg::RectangleU hitbox{};
};
