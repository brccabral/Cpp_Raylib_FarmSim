#pragma once
#include "GenericSprite.h"


class Water : public GenericSprite
{
public:

    Water(Vector2 pos, const std::vector<Surface *> &frames, const std::vector<SpriteGroup *> &sprite_groups);
    ~Water() override;

private:

    std::vector<Surface *> frames;
    float frame_index = 0.0f;
};
