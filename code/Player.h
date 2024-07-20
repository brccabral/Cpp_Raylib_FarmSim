#pragma once
#include <raylib_utils.h>


class Player : public SimpleSprite
{
public:

    Player(Vector2 pos, SpriteGroup *group);
    ~Player() override;
};
