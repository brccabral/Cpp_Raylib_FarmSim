#pragma once
#include "CameraGroup.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Overlay.hpp"
#include "Rain.hpp"
#include "Sky.hpp"
#include "SoilLayer.hpp"
#include "Transition.hpp"
#include "Sprites/GenericSprite.hpp"
#include "Sprites/Interaction.hpp"
#include "Sprites/Tree.hpp"
#include "Sprites/Water.hpp"
#include "Sprites/WildFlower.hpp"


class Level
{
public:

    Level();
    Level(const Level &other) = delete;
    Level(Level &&other) = default;
    Level &operator=(const Level &other) = delete;
    Level &operator=(Level &&other) = default;
    ~Level();
    void run(float dt);
    void Setup();

private:

    void PlayerAdd(const std::string &item) const;
    void Reset();
    void PlantCollision();
    void ToogleShop();

    rg::Surface *display_surface = &rg::display::GetSurface();

    CameraGroup all_sprites{};
    rg::sprite::Group collisionSprites{};
    rg::sprite::Group treeSprites{};
    rg::sprite::Group interactionSprites{};
    // player must be allocated on Heap due to Timer lambda functions are temporary
    Player *player{};
    Overlay overlay{};
    Transition transition{};
    SoilLayer soil_layer{};
    Sky sky{};
    Rain rain{};
    Menu menu{};
    std::vector<GenericSprite> generic_sprites_;
    std::vector<Water> water_sprites_;
    std::vector<WildFlower> wild_flowers_sprites_;
    std::vector<Tree> trees_sprites_;
    std::vector<Interaction> interactions_sprites_;

    rl::tmx_map *tmx_data = nullptr;
    std::unordered_map<unsigned int, rg::Surface> level_surfaces{};
    std::unordered_map<std::string, rg::Surface> stump_surfaces{};
    rg::Frames water_frames{};

    bool raining{};
    bool shop_active{};

    // music
    rg::mixer::Sound success = rg::mixer::Sound("resources/audio/success.wav");
    rg::mixer::Sound music = rg::mixer::Sound("resources/audio/music.mp3", true);

    rg::Surface ground_surf{};
    rg::Surface apple_surf{};
};
