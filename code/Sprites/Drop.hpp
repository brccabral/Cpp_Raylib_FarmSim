#pragma once
#include "GenericSprite.hpp"


class Drop : public GenericSprite
{
public:

    Drop(rg::math::Vector2 pos, const rg::Surface_Ptr &surface, unsigned int z,
         bool moving);
    ~Drop() override;
    void Update(float deltaTime) override;

private:

    int lifetime{};
    double start_time{};

    bool moving{};
    rg::math::Vector2 direction{};
    unsigned int speed{};
};
