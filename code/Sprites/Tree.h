#pragma once
#include "GenericSprite.h"


class Tree : public GenericSprite
{
public:

    Tree(rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::SpriteGroup *> &groups, const char *name);
    ~Tree() override;
    void LeaveOtherGroups(const rg::SpriteGroup *sprite_group) override;
    void Damage();
    void Update(float deltaTime) override;

private:

    void CreateFruit();
    void CheckDeath();

    std::string name_;

    std::vector<rl::Vector2> apple_pos{};
    rg::SpriteGroup apple_sprites{};

    int health = 5;
    bool alive = true;
    rg::Surface *stump_surf = nullptr;

    rg::Timer invul_timer = rg::Timer(0.2f);
};
