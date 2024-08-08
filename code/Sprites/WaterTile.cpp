#include "WaterTile.h"
#include "../Settings.h"


WaterTile::WaterTile(
        const rg::math::Vector2 pos, rg::Surface *surface,
        const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner)
    : Sprite(groups, owner)
{
    image = surface;
    rect = image->GetRect().topleft(pos);
    z = LAYERS["soil water"];
}

WaterTile::~WaterTile()
{
    // image is deleted in ~SoilLayer();
    image = nullptr;
}
