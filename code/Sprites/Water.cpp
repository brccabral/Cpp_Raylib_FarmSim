#include "Water.h"

Water::Water(
        const rg::math::Vector2 pos, rg::Frames *frames,
        const std::vector<rg::sprite::Group *> &sprite_groups)
    : GenericSprite(pos, frames, sprite_groups, LAYERS["water"]), frames(frames)
{}

Water::~Water()
{
    // image is a pointer to frames
    // but frames is deleted in the Level class
    // and the image is deleted in ~Sprite()
    image = nullptr;
}

void Water::Update(const float deltaTime)
{
    Animate(deltaTime);
}

void Water::Animate(const float dt)
{
    frame_index += 5 * dt;
    frames->SetAtlas(int(frame_index));
}
