#include "Player.h"
#include <raymath.h>

Player::Player(const Vector2 pos, SpriteGroup *group) : SimpleSprite(group)
{
    ImportAssets();

    image = animations[status][frame_index];

    rect = image->GetRect();
    RectToCenter(rect, pos);
}

Player::~Player()
{
    for (auto &[key, surfaces]: animations)
    {
        for (const auto *surface: surfaces)
        {
            delete surface;
        };
    }
}

void Player::Input()
{
    if (IsKeyDown(KEY_UP))
    {
        direction.y = -1;
        status = "up";
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        direction.y = 1;
        status = "down";
    }
    else
    {
        direction.y = 0;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        direction.x = 1;
        status = "right";
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        direction.x = -1;
        status = "left";
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
    Animate(deltaTime);
}

void Player::Animate(const float dt)
{
    frame_index += 4 * dt;
    if (frame_index >= animations[status].size())
    {
        frame_index = 0;
    }
    image = animations[status][int(frame_index)];
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

void Player::ImportAssets()
{
    animations["up"] = {};
    animations["down"] = {};
    animations["left"] = {};
    animations["right"] = {};
    animations["up_idle"] = {};
    animations["down_idle"] = {};
    animations["left_idle"] = {};
    animations["right_idle"] = {};
    animations["up_hoe"] = {};
    animations["down_hoe"] = {};
    animations["left_hoe"] = {};
    animations["right_hoe"] = {};
    animations["up_axe"] = {};
    animations["down_axe"] = {};
    animations["left_axe"] = {};
    animations["right_axe"] = {};
    animations["up_water"] = {};
    animations["down_water"] = {};
    animations["left_water"] = {};
    animations["right_water"] = {};

    for (auto &[key, surfaces]: animations)
    {
        std::string path = "resources/graphics/character/" + key;
        surfaces = ImportFolder(path.c_str());
    }
}
