#pragma once
#include "GenericSprite.h"


// Decoration layer (not just flowers)
class WildFlower : public GenericSprite
{
public:

    WildFlower(
            rg::math::Vector2 pos, rg::Surface *surf,
            const std::vector<rg::sprite::Group *> &groups);
};
