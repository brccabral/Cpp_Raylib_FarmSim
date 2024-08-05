#include "SoilTile.h"

#include "../Settings.h"


SoilTile::SoilTile(
        const rg::math::Vector2 pos, rg::Surface *surface,
        const std::vector<rg::sprite::Group *> &groups)
    : Sprite(groups)
{
    image = surface;
    rect = image->GetRect().topleft(pos);
    z = LAYERS["soil"];
}
