#pragma once
#include <rygame.h>
#include "GenericSprite.h"


class Plant : public GenericSprite
{
public:

    Plant(rl::Vector2 pos, const std::vector<rg::sprite::Group *> &groups,
          const std::string &plant_type,
          const std::function<bool(rl::Vector2 target)> &check_watered);
    ~Plant() override;
    void Grow();

    bool harvestable{};

private:

    std::string plant_type;
    std::vector<rg::Surface *> frames{};
    float age = 0;
    int max_age{};
    float grow_speed{};
    float y_offset{};
    std::function<bool(rl::Vector2 target)> check_watered;
};
