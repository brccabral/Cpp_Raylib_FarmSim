#pragma once
#include <raylib_utils.h>
#include "../Settings.h"


class GenericSprite : public SimpleSprite
{
public:

    GenericSprite(
            Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, unsigned int z = LAYERS["main"]);

    RectangleU hitbox{};
};
