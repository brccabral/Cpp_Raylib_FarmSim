#pragma once
#include <raylib_utils.h>
#include "../Settings.h"


class GenericSprite : public rg::sprite::Sprite
{
public:

    GenericSprite(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups,
            unsigned int z = LAYERS["main"]);
    void InitImage(rl::Vector2 pos, rg::Surface *surf);

    rg::RectangleU hitbox{};
};
