#pragma once
#include "GenericSprite.h"


class Tree : public GenericSprite
{
public:

    Tree(Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, std::string name);
    ~Tree() override;
    void LeaveOtherGroups(const SpriteGroup *sprite_group) override;
    void Damage();

private:

    void CreateFruit();

    std::string name_;

    std::vector<Vector2> apple_pos{};
    SpriteGroup apple_sprites{};

    int health = 5;
    bool alive = true;
    Surface *stump_surf = nullptr;

    Timer invul_timer = Timer(0.2f);
};
