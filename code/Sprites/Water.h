#pragma once
#include "GenericSprite.h"


class Water : public GenericSprite
{
public:

    Water(rg::math::Vector2 pos, rg::Frames *frames,
          const std::vector<rg::sprite::Group *> &sprite_groups);
    ~Water() override;
    void Update(float deltaTime) override;

private:

    void Animate(float dt);

    rg::Frames *frames = nullptr;
    float frame_index = 0.0f;
};
