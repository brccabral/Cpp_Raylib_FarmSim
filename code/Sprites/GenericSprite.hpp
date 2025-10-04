#pragma once
#include <rygame.hpp>
#include "../Settings.hpp"


class GenericSprite : public rg::sprite::Sprite
{
public:

    GenericSprite() = default;
    GenericSprite(
            rg::math::Vector2<float> pos, rg::Surface *surf,
            unsigned int z = Settings::GetInstance().LAYERS["main"]);
    void InitImage(rg::Surface *surf);

    rg::Rect hitbox{};
};
