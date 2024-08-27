#pragma once
#include "GenericSprite.hpp"


class Tree : public GenericSprite
{
public:

    Tree(rg::math::Vector2 pos, const rg::Surface_Ptr &surf, const char *name,
         const std::function<void(const std::string &item)> &player_add);
    void Damage();
    void Update(float deltaTime) override;
    void CreateFruit();
    rg::sprite::Group apple_sprites{};

private:

    void CheckDeath();

    std::string name_;

    std::vector<rg::math::Vector2> apple_pos{};

    int health = 5;
    bool alive = true;
    rg::Surface_Ptr stump_surf = nullptr;
    rg::Surface_Ptr apple_surf = nullptr;

    std::function<void(const std::string &item)> player_add;
};
