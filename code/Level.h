#pragma once
#include <raylib_utils.h>


class Level
{
public:

    Level();
    void run(float dt);

private:

    SpriteGroup all_sprites;
};
