#include "Player.h"
#include <raymath.h>

Player::Player(const Vector2 pos, SpriteGroup *group) : SimpleSprite(group)
{
    ImportAssets();

    image = animations[status][frame_index];

    rect = image->GetRect();
    RectToCenter(rect, pos);

    timers["tool use"] = Timer(0.350f, false, false, [this] { UseTool(); });
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
        direction_status = "up";
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        direction.y = 1;
        direction_status = "down";
    }
    else
    {
        direction.y = 0;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        direction.x = 1;
        direction_status = "right";
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        direction.x = -1;
        direction_status = "left";
    }
    else
    {
        direction.x = 0;
    }

    // tool use
    if (IsKeyPressed(KEY_SPACE))
    {
        timers["tool use"].Activate();
    }
}

void Player::Update(const float deltaTime)
{
    for (auto &[key, timer]: timers)
    {
        timer.Update();
    }
    Input();
    UpdateStatus();
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

void Player::UpdateStatus()
{
    if (Vector2Length(direction) == 0)
    {
        animation_status = "_idle";
    }
    else if (timers["tool use"].active)
    {
        animation_status = "_" + selected_tool;
    }
    else
    {
        animation_status = "";
    }
    status = direction_status + animation_status;
}

void Player::UseTool()
{
    std::string tool = selected_tool;
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
