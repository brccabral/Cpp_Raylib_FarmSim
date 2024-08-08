#pragma once
#include "GenericSprite.h"


class Tree : public GenericSprite
{
public:

    Tree(rg::math::Vector2 pos, const std::shared_ptr<rg::Surface> &surf, const char *name,
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
    std::shared_ptr<rg::Surface> stump_surf = nullptr;
    std::shared_ptr<rg::Surface> apple_surf = nullptr;

    std::function<void(const std::string &item)> player_add;
};
