#pragma once
#include "GenericSprite.h"


class Interaction : public GenericSprite
{
public:

    Interaction(
            rl::Vector2 pos, rl::Vector2 size, const std::vector<rg::sprite::Group *> &groups,
            std::string name);

    std::string name;
};
