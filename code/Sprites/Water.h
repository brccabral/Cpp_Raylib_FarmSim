#pragma once
#include "GenericSprite.h"


class Water : public GenericSprite
{
public:

    Water(rg::math::Vector2 pos, const std::vector<rg::Surface *> &frames,
          const std::vector<rg::sprite::Group *> &sprite_groups);
    ~Water() override;
    void Update(float deltaTime) override;

private:

    void Animate(float dt);

    std::vector<rg::Surface *> frames;
    float frame_index = 0.0f;
};
