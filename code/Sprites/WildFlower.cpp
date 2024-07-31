#include "WildFlower.h"

WildFlower::WildFlower(
        const rg::math::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups)
    : GenericSprite(pos, surf, groups)
{}
