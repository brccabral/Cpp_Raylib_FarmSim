#pragma once
#include "GenericSprite.hpp"
#include "Particle.hpp"
#include "../CameraGroup.hpp"


class Tree : public GenericSprite
{
public:

    Tree(
            rg::math::Vector2<float> pos, rg::Surface *surf, rg::Surface *apple_surf,
            rg::Surface *stump_surf, const char *name, CameraGroup *all_sprites,
            const std::function<void(const std::string &item)> &player_add);
    void Damage();
    void Update(float deltaTime) override;
    void CreateFruit();
    rg::sprite::Group apple_sprites{};

private:

    CameraGroup *all_sprites{};

    void CheckDeath();

    std::string name_;

    // std::vector<rg::math::Vector2> apple_pos{};

    int health = 5;
    bool alive = true;
    rg::Surface *stump_surf;
    rg::Surface *apple_surf;

    std::vector<GenericSprite> apples_sprites_;
    std::vector<Particle> particles_sprites_;

    std::function<void(const std::string &item)> player_add;
};
