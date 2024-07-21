#pragma once
#include "CameraGroup.h"
#include "Overlay.h"
#include "Player.h"


class Level
{
public:

    Level();
    ~Level();
    void run(float dt);
    void Setup();

private:

    CameraGroup all_sprites{};
    Player *player = nullptr;
    Overlay *overlay = nullptr;
};
