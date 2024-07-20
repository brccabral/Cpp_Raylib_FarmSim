#include "Player.h"
#include <raymath.h>

Player::Player(const Vector2 pos, SpriteGroup *group) : SimpleSprite(group)
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

void Player::Input()
{
    if (IsKeyDown(KEY_UP))
    {
        direction.y = -1;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        direction.y = 1;
    }
    else
    {
        direction.y = 0;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        direction.x = 1;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        direction.x = -1;
    }
    else
    {
        direction.x = 0;
    }
}

void Player::Update(const float deltaTime)
{
    Input();
    Move(deltaTime);
}

void Player::Move(const float dt)
{
    direction = Vector2Normalize(direction);
    // split the movement to deal with collisions
    // horizontal movement
    rect.pos.x += direction.x * speed * dt;
    // vertical movement
    rect.pos.y += direction.y * speed * dt;
}
