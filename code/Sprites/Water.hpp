#pragma once
#include "GenericSprite.hpp"


class Water : public GenericSprite
{
public:

    Water(rg::math::Vector2 pos, const rg::Frames_Ptr &frames);
    ~Water() override;
    void Update(float deltaTime) override;

private:

    void Animate(float dt);

    rg::Frames_Ptr frames = nullptr;
    float frame_index = 0.0f;
};
