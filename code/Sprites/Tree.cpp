#include "Tree.h"

#include <utility>

Tree::Tree(const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, std::string name)
    : GenericSprite(pos, surf, groups), name(std::move(name))
{}
