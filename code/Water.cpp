#include "Water.h"

Water::Water(const Vector2 pos, const std::vector<Surface *> &frames, const std::vector<SpriteGroup *> &sprite_groups)
    : GenericSprite(pos, frames[0], sprite_groups, LAYERS["water"]), frames(frames)
{}

Water::~Water()
{
    // image is a pointer to one of the frames
    // but the frames are deleted in the Level class
    // and the image is deleted in the SimpleSprite parent
    image = nullptr;
}
