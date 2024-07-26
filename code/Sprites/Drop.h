#pragma once
#include "GenericSprite.h"


class Drop : public GenericSprite
{
public:
    Drop(rl::Vector2 pos, rg::Surface* surface, const std::vector<rg::sprite::Group*>& groups,
         unsigned int z, bool moving);
    ~Drop() override;
    void Update(float deltaTime) override;

private:
    int lifetime{};
    double start_time{};

    bool moving{};
    rl::Vector2 direction{};
    unsigned int speed{};
};
