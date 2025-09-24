#include "Water.hpp"

Water::Water(const rg::math::Vector2 pos, rg::Frames *frames)
    : GenericSprite(pos, frames, LAYERS["water"]), frames(frames)
{
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
