#pragma once
#include "GenericSprite.hpp"


class Interaction : public GenericSprite
{
public:

    Interaction() = default;
    Interaction(rg::math::Vector2<float> pos, rg::math::Vector2<float> size, std::string name);
    Interaction(const Interaction &other) = delete;
    Interaction &operator=(const Interaction &other) = delete;
    Interaction(Interaction &&other) = default;
    Interaction &operator=(Interaction &&other) = default;
    ~Interaction() override;

    std::string name{};
};
