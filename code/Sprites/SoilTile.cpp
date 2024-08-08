#include "SoilTile.h"

#include "../Settings.h"


SoilTile::SoilTile(const rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surface)
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
