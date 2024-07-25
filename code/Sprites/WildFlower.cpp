#include "WildFlower.h"

WildFlower::WildFlower(const rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::SpriteGroup *> &groups)
    : GenericSprite(pos, surf, groups)
{
    hitbox = rect;
    RectInflate(hitbox, -rect.width * 0.2f, -rect.height * 0.75f);
    RectToMidBottom(hitbox, GetRectMidBottom(rect));
}
