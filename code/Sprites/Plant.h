#pragma once
#include <rygame.h>


class Plant : public rg::sprite::Sprite
{
public:

    Plant(rl::Vector2 pos, const std::vector<rg::sprite::Group *> &groups,
          const std::string &plant_type);
    ~Plant() override;

private:

    std::string plant_type;
    std::vector<rg::Surface *> frames{};
    int age = 0;
    int max_age{};
    float grow_speed{};
    float y_offset{};
};
