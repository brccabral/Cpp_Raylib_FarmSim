#pragma once
#include <raylib_utils.h>
#include "Player.h"


class CameraGroup : public rg::SpriteGroup
{
public:

    void CustomDraw(const Player *player);

private:

    rl::Vector2 offset{};
};
