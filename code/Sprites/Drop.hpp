#pragma once
#include "GenericSprite.hpp"


class Drop : public GenericSprite
{
public:

    Drop() = default;
    Drop(
            rg::math::Vector2 pos, rg::Surface *surface, unsigned int z,
            bool moving);
    void Update(float deltaTime) override;

    bool is_alive{};

private:

    int lifetime{};
    double start_time{};

    bool moving{};
    rg::math::Vector2 direction{};
    unsigned int speed{};
};
