#include "Water.h"

Water::Water(
        const rl::Vector2 pos, const std::vector<rg::Surface *> &frames,
        const std::vector<rg::SpriteGroup *> &sprite_groups)
    : GenericSprite(pos, frames[0], sprite_groups, LAYERS["water"]), frames(frames)
{}

Water::~Water()
{
    // image is a pointer to one of the frames
    // but the frames are deleted in the Level class
    // and the image is deleted in the SimpleSprite parent
    image = nullptr;
}

void Water::Update(const float deltaTime)
{
    Animate(deltaTime);
}

void Water::Animate(const float dt)
{
    frame_index += 5 * dt;
    if (frame_index >= frames.size())
    {
        frame_index = 0;
    }
    image = frames[int(frame_index)];
}
