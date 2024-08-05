#pragma once
#include "CameraGroup.h"
#include "Menu.h"
#include "Player.h"
#include "Overlay.h"
#include "Rain.h"
#include "Sky.h"
#include "SoilLayer.h"
#include "Transition.h"


class Level
{
public:

    Level();
    ~Level();
    void run(float dt);
    void Setup();

private:

    void PlayerAdd(const std::string &item) const;
    void Reset();
    void PlantCollision();
    void ToogleShop();

    rg::Surface *display_surface = rg::display::GetSurface();

    CameraGroup all_sprites{};
    rg::sprite::Group collisionSprites{};
    rg::sprite::Group treeSprites{};
    rg::sprite::Group interactionSprites{};
    Player *player = nullptr;
    Overlay *overlay = nullptr;
    Transition *transition = nullptr;
    SoilLayer *soil_layer = nullptr;
    Sky *sky = nullptr;
    Rain *rain = nullptr;
    Menu *menu = nullptr;

    rl::tmx_map *tmx_data = nullptr;
    rg::Frames *water_frames = nullptr;

    bool raining{};
    bool shop_active{};

    // music
    rg::mixer::Sound success = rg::mixer::Sound("resources/audio/success.wav");
    rg::mixer::Sound music = rg::mixer::Sound("resources/audio/music.mp3", true);

    rg::Surface *ground_surf = nullptr;
};
