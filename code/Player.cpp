#include <cstdio>
#include <cstring>
#include "Player.h"
#include "Settings.h"
#include "Sprites/GenericSprite.h"
#include "Sprites/Interaction.h"
#include "Sprites/Tree.h"

#define HITBOX_Y_OFFSET 15

Player::Player(
        const rl::Vector2 pos, rg::sprite::Group *group, rg::sprite::Group *collisionSprites,
        rg::sprite::Group *treeSprites, rg::sprite::Group *interactionSprites,
        SoilLayer *soil_layer)
    : Sprite(group), collisionSprites(collisionSprites), treeSprites(treeSprites),
      interactionSprites(interactionSprites), soil_layer(soil_layer)
{
    ImportAssets();

    image = animations[status][frame_index];

    rect = image->GetRect();
    RectToCenter(rect, pos);

    z = LAYERS["main"];

    timers["tool use"] = rg::Timer(0.350f, false, false, [this] { UseTool(); });
    timers["tool switch"] = rg::Timer(0.2f);
    timers["seed use"] = rg::Timer(0.350f, false, false, [this] { UseSeed(); });
    timers["seed switch"] = rg::Timer(0.2f);

    hitbox = rect;
    RectInflate(hitbox, -126, -70);
    hitbox.y += HITBOX_Y_OFFSET;
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
    // but it is also deleted in the Sprite parent class
    image = nullptr;
}

void Player::Input()
{
    // player can't move when tool is in use
    if (timers["tool use"].active || sleep)
    {
        return;
    }
    if (IsKeyDown(rl::KEY_UP))
    {
        direction.y = -1;
        direction_status = "up";
        SetStatus("");
    }
    else if (IsKeyDown(rl::KEY_DOWN))
    {
        direction.y = 1;
        direction_status = "down";
        SetStatus("");
    }
    else
    {
        direction.y = 0;
    }

    if (IsKeyDown(rl::KEY_RIGHT))
    {
        direction.x = 1;
        direction_status = "right";
        SetStatus("");
    }
    else if (IsKeyDown(rl::KEY_LEFT))
    {
        direction.x = -1;
        direction_status = "left";
        SetStatus("");
    }
    else
    {
        direction.x = 0;
    }

    // tool use
    if (IsKeyPressed(rl::KEY_SPACE))
    {
        timers["tool use"].Activate();
        direction = {};
        frame_index = 0;
    }

    // change tool
    // the timer is not needed in here because we are using IsKeyReleased, but it is here to be
    // compliant with the tutorial
    if (IsKeyReleased(rl::KEY_Q) && !timers["tool switch"].active)
    {
        timers["tool switch"].Activate();
        tool_index += 1;
        tool_index %= tools.size();
        selected_tool = tools[tool_index];
    }

    // seed use
    if (IsKeyPressed(rl::KEY_LEFT_CONTROL))
    {
        timers["seed use"].Activate();
        direction = {};
        frame_index = 0;
    }

    // change seed
    // the timer is not needed in here because we are using IsKeyReleased, but it is here to be
    // compliant with the tutorial
    if (IsKeyReleased(rl::KEY_E) && !timers["seed switch"].active)
    {
        timers["seed switch"].Activate();
        seed_index += 1;
        seed_index %= seeds.size();
        selected_seed = seeds[seed_index];
    }

    // interation sprites
    if (IsKeyReleased(rl::KEY_ENTER))
    {
        if (auto *collided_interation_sprite = spritecollideany(this, interactionSprites))
        {
            const auto *interaction_sprite = (Interaction *) collided_interation_sprite;
            if (!strcmp(interaction_sprite->name.c_str(), "Trader"))
            {}
            else
            {
                direction_status = "left";
                SetStatus("_idle");
                sleep = true;
            }
        }
    }
}

void Player::UpdateTimers()
{
    for (auto &[key, timer]: timers)
    {
        timer.Update();
    }
}
void Player::Update(const float deltaTime)
{
    Input();
    UpdateStatus();
    UpdateTimers();
    GetTargetPos();

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
        SetStatus("_idle");
    }

    if (timers["tool use"].active)
    {
        SetStatus("_" + selected_tool);
    }
}

void Player::UseTool() const
{
    if (!strcmp(selected_tool.c_str(), "hoe"))
    {
        soil_layer->GetHit(target_pos);
    }
    else if (!strcmp(selected_tool.c_str(), "axe"))
    {
        for (const auto treeSprite: treeSprites->Sprites())
        {
            const auto tree = (Tree *) treeSprite;
            if (CheckCollisionPointRec(target_pos, tree->rect.rectangle))
            {
                tree->Damage();
            }
        }
    }
    else if (!strcmp(selected_tool.c_str(), "water"))
    {
        soil_layer->Water(target_pos);
    }
}

void Player::UseSeed() const
{
    soil_layer->PlantSeed(target_pos, selected_seed);
}

void Player::Collision(const rg::Axis axis)
{
    // only GenericSprite should be added to collisionSprites as GenericSprite has hitbox
    for (auto *sprite: collisionSprites->Sprites())
    {
        const auto *generic_sprite = (GenericSprite *) sprite;
        if (CheckCollisionRecs(generic_sprite->hitbox.rectangle, hitbox.rectangle))
        {
            if (axis == rg::HORIZONTAL)
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
            rl::Vector2 newPos = GetRectCenter(hitbox);
            newPos.y -= HITBOX_Y_OFFSET;
            RectToCenter(rect, newPos);
        }
    }
}

void Player::GetTargetPos()
{
    target_pos = GetRectCenter(rect) + PLAYER_TOOL_OFFSET[direction_status];
}

void Player::SetStatus(const std::string &animation_status)
{
    status = direction_status + animation_status;
}

void Player::Move(const float dt)
{
    direction = Vector2Normalize(direction);

    // split the movement to deal with collisions
    // horizontal movement
    rect.pos.x += direction.x * speed * dt;
    RectToCenter(hitbox, GetRectCenter(rect));
    hitbox.y += HITBOX_Y_OFFSET;
    Collision(rg::HORIZONTAL);

    // vertical movement
    rect.pos.y += direction.y * speed * dt;
    RectToCenter(hitbox, GetRectCenter(rect));
    hitbox.y += HITBOX_Y_OFFSET;
    Collision(rg::VERTICAL);
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
        surfaces = rg::assets::ImportFolder(path.c_str());

#ifdef SHOW_HITBOX
        for (const auto *surface: surfaces)
        {
            const rg::RectangleU rd = surface->GetRect();
            DrawRect(surface, rl::RED, rd, 2);
            rg::RectangleU hd = rd;
            RectInflate(hd, -126, -70);
            hd.y += HITBOX_Y_OFFSET;
            DrawRect(surface, rl::GREEN, hd, 2);
        }
#endif
    }
}
