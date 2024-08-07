#include "WildFlower.h"

WildFlower::WildFlower(
        const rg::math::Vector2 pos, rg::Surface *surf,
        const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner)
    : GenericSprite(pos, surf, groups, owner)
{}
