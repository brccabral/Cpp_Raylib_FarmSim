#pragma once
#include "GenericSprite.hpp"


class Interaction : public GenericSprite
{
public:

    Interaction(rg::math::Vector2 pos, rg::math::Vector2 size, std::string name);

    std::string name;
};
