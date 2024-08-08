#pragma once
#include "GenericSprite.h"


class Drop : public GenericSprite
{
public:

    Drop(rg::math::Vector2 pos, rg::Surface *surface,
         const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner,
         unsigned int z, bool moving);
    ~Drop() override;
    void Update(float deltaTime) override;

private:

    int lifetime{};
    double start_time{};

    bool moving{};
    rg::math::Vector2 direction{};
    unsigned int speed{};
};
