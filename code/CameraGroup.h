#pragma once
#include <raylib_utils.h>
#include "Player.h"


class CameraGroup : public SpriteGroup
{
public:

    void CustomDraw(const Player *player);

private:

    Vector2 offset{};
};
