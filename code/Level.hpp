#pragma once
#include "CameraGroup.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Overlay.hpp"
#include "Rain.hpp"
#include "Sky.hpp"
#include "SoilLayer.hpp"
#include "Transition.hpp"


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

    void PlayerAdd(const std::string &item);
    void Reset();
    void PlantCollision();
    void ToogleShop();

    rg::Surface *display_surface = &rg::display::GetSurface();

    CameraGroup all_sprites{};
    rg::sprite::Group collisionSprites{};
    rg::sprite::Group treeSprites{};
    rg::sprite::Group interactionSprites{};
    Player player{};
    Overlay overlay{};
    Transition transition{};
    SoilLayer soil_layer{};
    Sky sky{};
    Rain rain{};
    Menu menu{};

    rl::tmx_map *tmx_data = nullptr;
    rg::Frames water_frames{};

    bool raining{};
    bool shop_active{};

    // music
    rg::mixer::Sound success = rg::mixer::Sound("resources/audio/success.wav");
    rg::mixer::Sound music = rg::mixer::Sound("resources/audio/music.mp3", true);

    rg::Surface ground_surf{};
};
