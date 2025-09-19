#pragma once
#include "GenericSprite.hpp"


class Water : public GenericSprite
{
public:

    Water(rg::math::Vector2 pos, rg::Frames *frames);
    ~Water() override;
    void Update(float deltaTime) override;

private:

    void Animate(float dt);

    rg::Frames *frames = nullptr;
    float frame_index = 0.0f;
};
