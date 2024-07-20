#include "Player.h"

Player::Player(Vector2 pos, SpriteGroup *group) : SimpleSprite(group)
{
    image = new Surface(32, 64);
    image->Fill(GREEN);

    rect = image->GetRect();
    RectToCenter(rect, pos);
}

Player::~Player()
{
    delete image;
}
