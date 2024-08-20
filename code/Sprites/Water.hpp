#pragma once
#include "GenericSprite.hpp"


class Water : public GenericSprite
{
public:

    Water(rg::math::Vector2 pos, const std::shared_ptr<rg::Frames> &frames);
    ~Water() override;
    void Update(float deltaTime) override;

private:

    void Animate(float dt);

    std::shared_ptr<rg::Frames> frames = nullptr;
    float frame_index = 0.0f;
};
