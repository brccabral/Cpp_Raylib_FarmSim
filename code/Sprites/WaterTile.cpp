#include "WaterTile.h"
#include "../Settings.h"


WaterTile::WaterTile(
        const rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surface)
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
