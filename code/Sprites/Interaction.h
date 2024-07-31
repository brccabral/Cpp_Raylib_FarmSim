#pragma once
#include "GenericSprite.h"


class Interaction : public GenericSprite
{
public:

    Interaction(
            rg::math::Vector2 pos, rg::math::Vector2 size, const std::vector<rg::sprite::Group *> &groups,
            std::string name);

    std::string name;
};
