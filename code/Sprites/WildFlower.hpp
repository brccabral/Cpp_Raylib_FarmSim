#pragma once
#include "GenericSprite.hpp"


// Decoration layer (not just flowers)
class WildFlower : public GenericSprite
{
public:

    WildFlower(rg::math::Vector2 pos, const rg::Surface_Ptr &surf);
};
