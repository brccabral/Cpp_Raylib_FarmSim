#include "WildFlower.h"

WildFlower::WildFlower(
        const rg::math::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups)
    : GenericSprite(pos, surf, groups)
{
    // hitbox = rect.copy();
    // hitbox.inflate(-rect.width * 0.2f, -rect.height * 0.75);
    // hitbox.midbottom(rect.midbottom());
}
