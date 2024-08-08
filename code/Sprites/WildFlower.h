#pragma once
#include "GenericSprite.h"


// Decoration layer (not just flowers)
class WildFlower : public GenericSprite
{
public:

    WildFlower(rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surf);
};
