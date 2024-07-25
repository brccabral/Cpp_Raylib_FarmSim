#pragma once
#include "CameraGroup.h"
#include "Player.h"
#include "Overlay.h"


class Level
{
public:

    Level();
    ~Level();
    void run(float dt);
    void Setup();

private:

    rg::Surface *display_surface = nullptr;

    CameraGroup all_sprites{};
    rg::SpriteGroup collisionSprites{};
    rg::SpriteGroup treeSprites{};
    Player *player = nullptr;
    Overlay *overlay = nullptr;

    rl::tmx_map *tmx_data = nullptr;
    std::vector<rg::Surface *> water_frames;
};
