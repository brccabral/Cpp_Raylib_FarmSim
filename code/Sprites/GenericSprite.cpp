#include "GenericSprite.h"

GenericSprite::GenericSprite(
        const rg::math::Vector2 pos, rg::Surface *surf,
        const std::vector<rg::sprite::Group *> &groups, const unsigned int z)
    : Sprite(groups)
{
    this->z = z;

    image = surf;
    rect = image->GetRect().topleft(pos);

    // hitbox gives an idea of pseudo-3D, where the player can be behind an object and vice-versa
    hitbox = rect.copy()
                     .inflate(-rect.width * 0.2f, -rect.height * 0.75f)
                     .midbottom(rect.midbottom());
}
