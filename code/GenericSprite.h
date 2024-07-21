#pragma once
#include <raylib_utils.h>


class GenericSprite : public SimpleSprite
{
public:

    GenericSprite(Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups);
};
