#pragma once
#include "GenericSprite.h"


class Tree : public GenericSprite
{
public:

    Tree(Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, std::string name);

private:

    std::string name;
};
