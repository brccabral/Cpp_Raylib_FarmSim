#pragma once
#include <rygame.hpp>
#include "../Settings.h"


class GenericSprite : public rg::sprite::Sprite
{
public:

    GenericSprite(
            rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surf,
            unsigned int z = LAYERS["main"]);
    void InitImage(const std::shared_ptr<rg::Surface> &surf);

    rg::Rect hitbox{};
};
