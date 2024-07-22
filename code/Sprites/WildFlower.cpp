#include "WildFlower.h"

WildFlower::WildFlower(const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups)
    : GenericSprite(pos, surf, groups)
{
    hitbox = rect;
    RectInflate(hitbox, -rect.width * 0.2f, -rect.height * 0.75f);
}
