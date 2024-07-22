#include "Player.h"
#include <raymath.h>
#include "Settings.h"
#include "Sprites/GenericSprite.h"

Player::Player(const Vector2 pos, SpriteGroup &group, SpriteGroup *collisionSprites)
    : SimpleSprite(group), collisionSprites(collisionSprites)
{
    ImportAssets();

    image = animations[status][frame_index];

    rect = image->GetRect();
    RectToCenter(rect, pos);

    z = LAYERS["main"];

    timers["tool use"] = Timer(0.350f, false, false, [this] { UseTool(); });
    timers["tool switch"] = Timer(0.2f);
    timers["seed use"] = Timer(0.350f, false, false, [this] { UseSeed(); });
    timers["seed switch"] = Timer(0.2f);

    hitbox = rect;
    RectInflate(hitbox, -126, -70);
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
    // image is a pointer to one of the animations
    // but it is also deleted in the SimpleSprite parent class
    image = nullptr;
}

void Player::Input()
{
    // player can't move when tool is in use
    if (timers["tool use"].active)
    {
        return;
    }
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
        direction = {};
        frame_index = 0;
    }

    // change tool
    // the timer is not needed in here because we are using IsKeyReleased, but it is here to be
    // compliant with the tutorial
    if (IsKeyReleased(KEY_Q) && !timers["tool switch"].active)
    {
        timers["tool switch"].Activate();
        tool_index += 1;
        tool_index %= tools.size();
        selected_tool = tools[tool_index];
    }

    // seed use
    if (IsKeyPressed(KEY_LEFT_CONTROL))
    {
        timers["seed use"].Activate();
        direction = {};
        frame_index = 0;
    }

    // change seed
    // the timer is not needed in here because we are using IsKeyReleased, but it is here to be
    // compliant with the tutorial
    if (IsKeyReleased(KEY_E) && !timers["seed switch"].active)
    {
        timers["seed switch"].Activate();
        seed_index += 1;
        seed_index %= seeds.size();
        selected_seed = seeds[seed_index];
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
    else
    {
        animation_status = "";
    }

    if (timers["tool use"].active)
    {
        animation_status = "_" + selected_tool;
    }
    status = direction_status + animation_status;
}

void Player::UseTool()
{
    std::string tool = selected_tool;
}

void Player::UseSeed()
{
    std::string seed = selected_seed;
}

void Player::Collision(const Axis axis)
{
    // only GenericSprite should be added to collisionSprites as collisionSprites has hitbox
    for (auto *sprite: collisionSprites->sprites)
    {
        const auto *generic_sprite = (GenericSprite *) sprite;
        if (CheckCollisionRecs(generic_sprite->hitbox.rectangle, hitbox.rectangle))
        {
            if (axis == HORIZONTAL)
            {
                if (direction.x > 0) // player moving right
                {
                    hitbox.x = generic_sprite->hitbox.x - hitbox.width;
                }
                else if (direction.x < 0) // player moving left
                {
                    hitbox.x = generic_sprite->hitbox.x + generic_sprite->hitbox.width;
                }
            }
            else
            {
                if (direction.y > 0) // player moving down
                {
                    hitbox.y = generic_sprite->hitbox.y - hitbox.height;
                }
                else if (direction.y < 0) // player moving up
                {
                    hitbox.y = generic_sprite->hitbox.y + generic_sprite->hitbox.height;
                }
            }
            RectToCenter(rect, GetRectCenter(hitbox));
        }
    }
}

void Player::Move(const float dt)
{
    direction = Vector2Normalize(direction);

    // split the movement to deal with collisions
    // horizontal movement
    rect.pos.x += direction.x * speed * dt;
    RectToCenter(hitbox, GetRectCenter(rect));
    Collision(HORIZONTAL);

    // vertical movement
    rect.pos.y += direction.y * speed * dt;
    RectToCenter(hitbox, GetRectCenter(rect));
    Collision(VERTICAL);
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
