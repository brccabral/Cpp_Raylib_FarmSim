#pragma once
#include <rygame.h>
#include "GenericSprite.h"


class Plant : public GenericSprite
{
public:

    Plant(rg::math::Vector2 pos, const std::vector<rg::sprite::Group *> &groups,
          const std::string &plant_type,
          const std::function<bool(rg::math::Vector2 target)> &check_watered);
    ~Plant() override;
    void Grow();

    bool harvestable{};
    std::string plant_type;

private:

    std::vector<rg::Surface *> frames{};
    float age = 0;
    int max_age{};
    float grow_speed{};
    float y_offset{};
    std::function<bool(rg::math::Vector2 target)> check_watered;
};
