#include "Water.h"

Water::Water(const rg::math::Vector2 pos, const std::shared_ptr<rg::Frames> &frames)
    : GenericSprite(pos, frames, LAYERS["water"]), frames(frames)
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
