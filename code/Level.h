#pragma once
#include <raylib_utils.h>

#include "Player.h"


class Level
{
public:

    Level();
    ~Level();
    void run(float dt);
    void Setup();

private:

    SpriteGroup all_sprites{};
    Player *player = nullptr;
};