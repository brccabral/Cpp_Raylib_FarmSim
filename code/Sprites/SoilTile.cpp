#include "SoilTile.h"

#include "../Settings.h"


SoilTile::SoilTile(
        const rl::Vector2 pos, rg::Surface *surface, const std::vector<rg::sprite::Group *> &groups)
    : Sprite(groups)
{
    image = surface;
    rect = {pos, (float) image->Texture()->width, (float) image->Texture()->height};
    z = LAYERS["soil"];
}

SoilTile::~SoilTile()
{
    // the image for SoilTile is created and deleted in SoilLayer (it is the same for all SoilTile)
    image = nullptr;
}
