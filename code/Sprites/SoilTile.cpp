#include "SoilTile.h"

#include "../Settings.h"


SoilTile::SoilTile(
        const rg::math::Vector2 pos, rg::Surface *surface,
        const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner)
    : Sprite(groups, owner)
{
    image = surface;
    rect = image->GetRect().topleft(pos);
    z = LAYERS["soil"];
}

SoilTile::~SoilTile()
{
    // image is deleted in ~SoilLayer();
    image = nullptr;
}
