#pragma once
#include "GenericSprite.h"
#include "../Level.h"


class Tree : public GenericSprite
{
public:

    Tree(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups, const char *name,
            const std::function<void(const std::string &item)> &player_add = [](const std::string &_) {});
    ~Tree() override;
    void LeaveOtherGroups(const rg::sprite::Group *sprite_group) override;
    void Damage();
    void Update(float deltaTime) override;

private:

    void CreateFruit();
    void CheckDeath();

    std::string name_;

    std::vector<rl::Vector2> apple_pos{};
    rg::sprite::Group apple_sprites{};

    int health = 5;
    bool alive = true;
    rg::Surface *stump_surf = nullptr;

    rg::Timer invul_timer = rg::Timer(0.2f);

    std::function<void(const std::string &item)> player_add;
};
