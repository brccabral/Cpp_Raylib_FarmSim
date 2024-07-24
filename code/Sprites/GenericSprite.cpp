#include "GenericSprite.h"

GenericSprite::GenericSprite(const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, unsigned int z)
    : SimpleSprite(groups)
{
    image = surf;
    rect = image->GetRect();
    RectToTopLeft(rect, pos);

    this->z = z;

    // hitbox gives an idea of pseudo-3D, where the player can be behind an object and vice-versa
    hitbox = rect;
    RectInflate(hitbox, -rect.width * 0.2f, -rect.height * 0.75f);
    RectToMidBottom(hitbox, GetRectMidBottom(rect));
}
