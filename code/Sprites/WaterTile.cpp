#include "WaterTile.h"
#include "../Settings.h"


WaterTile::WaterTile(
        const rl::Vector2 pos, rg::Surface *surface, const std::vector<rg::sprite::Group *> &groups)
    : Sprite(groups)
{
    image = surface;
    rect = {pos, (float) image->Texture()->width, (float) image->Texture()->height};
    z = LAYERS["soil water"];
}

WaterTile::~WaterTile()
{
    // the image for WaterTile is created and deleted in SoilLayer (it is the same for all
    // WaterTile)
    image = nullptr;
}
