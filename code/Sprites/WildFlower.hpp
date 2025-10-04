#pragma once
#include "GenericSprite.hpp"


// Decoration layer (not just flowers)
class WildFlower : public GenericSprite
{
public:

    WildFlower(rg::math::Vector2<float> pos, rg::Surface *surf);
};
