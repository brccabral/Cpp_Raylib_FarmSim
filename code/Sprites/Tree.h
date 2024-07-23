#pragma once
#include "GenericSprite.h"


class Tree : public GenericSprite
{
public:

    Tree(Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, std::string name);
    ~Tree() override;
    void LeaveOtherGroups(const SpriteGroup *sprite_group) override;

private:

    void CreateFruit();

    std::string name_;

    std::vector<Vector2> apple_pos{};
    SpriteGroup apple_sprites{};
};
