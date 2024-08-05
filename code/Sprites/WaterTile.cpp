#include "WaterTile.h"
#include "../Settings.h"


WaterTile::WaterTile(
        const rg::math::Vector2 pos, rg::Surface *surface,
        const std::vector<rg::sprite::Group *> &groups)
    : Sprite(groups)
{
    image = surface;
    rect = image->GetRect().topleft(pos);
    z = LAYERS["soil water"];
}
