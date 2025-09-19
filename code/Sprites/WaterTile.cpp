#include "WaterTile.hpp"
#include "../Settings.hpp"


WaterTile::WaterTile(const rg::math::Vector2 pos, rg::Surface *surface)
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
