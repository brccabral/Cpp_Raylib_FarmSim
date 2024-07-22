#pragma once
#include "GenericSprite.h"


// Decoration layer (not just flowers)
class WildFlower : public GenericSprite
{
public:

    WildFlower(Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups);
};
