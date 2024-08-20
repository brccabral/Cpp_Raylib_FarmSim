#pragma once
#include <rygame.hpp>
#include "GenericSprite.hpp"


class Plant : public GenericSprite
{
public:

    Plant(rg::math::Vector2 pos, const std::string &plant_type,
          const std::function<bool(rg::math::Vector2 target)> &check_watered);
    void Grow();

    bool harvestable{};
    std::string plant_type;

private:

    float age = 0;
    int max_age{};
    float grow_speed{};
    float y_offset{};
    std::function<bool(rg::math::Vector2 target)> check_watered;
};
