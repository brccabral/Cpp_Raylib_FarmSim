#include "SoilTile.hpp"
#include "../Settings.hpp"


SoilTile::SoilTile(const rg::math::Vector2 pos, const rg::Surface_Ptr &surface)
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
