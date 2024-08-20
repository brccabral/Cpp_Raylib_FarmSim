#include "GenericSprite.hpp"


GenericSprite::GenericSprite(
        const rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surf, const unsigned int z)
{
    this->z = z;

    rect.pos = pos;

    if (surf)
    {
        InitImage(surf);
    }
}

void GenericSprite::InitImage(const std::shared_ptr<rg::Surface> &surf)
{
    image = surf;
    rect.width = image->GetRect().width;
    rect.height = image->GetRect().height;

    // hitbox gives an idea of pseudo-3D, where the player can be behind an object and vice-versa
    hitbox = rect.copy()
                     .inflate(-rect.width * 0.2f, -rect.height * 0.75f)
                     .midbottom(rect.midbottom());
}
