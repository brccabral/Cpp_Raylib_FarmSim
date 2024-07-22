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

    CameraGroup all_sprites{};
    SpriteGroup collisionSprites{};
    Player *player = nullptr;
    Overlay *overlay = nullptr;

    tmx_map *tmx_data = nullptr;
    std::vector<Surface *> water_frames;
};
