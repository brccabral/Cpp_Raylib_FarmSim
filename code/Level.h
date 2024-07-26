#pragma once
#include "CameraGroup.h"
#include "Player.h"
#include "Overlay.h"
#include "Rain.h"
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

    void PlayerAdd(const std::string &item);
    void Reset();
    void PlantCollision();

    rg::Surface *display_surface = nullptr;

    CameraGroup all_sprites{};
    rg::sprite::Group collisionSprites{};
    rg::sprite::Group treeSprites{};
    rg::sprite::Group interactionSprites{};
    Player *player = nullptr;
    Overlay *overlay = nullptr;
    Transition *transition = nullptr;
    SoilLayer *soil_layer = nullptr;
    Rain *rain = nullptr;

    rl::tmx_map *tmx_data = nullptr;
    std::vector<rg::Surface *> water_frames;

    bool raining{};
};
