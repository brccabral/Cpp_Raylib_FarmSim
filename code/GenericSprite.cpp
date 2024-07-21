#include "GenericSprite.h"

GenericSprite::GenericSprite(const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups)
    : SimpleSprite(groups)
{
    image = surf;
    rect = image->GetRect();
    RectToTopLeft(rect, pos);
}
