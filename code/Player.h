#pragma once
#include <map>
#include <string>
#include <raylib_utils.h>


class Player : public rg::SimpleSprite
{
public:

    Player(rl::Vector2 pos, rg::SpriteGroup &group, rg::SpriteGroup *collisionSprites, rg::SpriteGroup *treeSprites);
    ~Player() override;
    void Update(float deltaTime) override;

    std::string direction_status = "down";

    std::vector<std::string> tools = {"hoe", "axe", "water"};
    std::string selected_tool = "hoe";

    std::vector<std::string> seeds = {"corn", "tomato"};
    std::string selected_seed = "corn";

    rg::RectangleU hitbox{};

private:

    void Move(float dt);
    void ImportAssets();
    void Input();
    void Animate(float dt);
    void UpdateStatus();
    void UseTool();
    void UseSeed();
    void Collision(rg::Axis axis);
    void GetTargetPos();

    rl::Vector2 direction{};
    float speed = 200.0f;

    std::map<std::string, std::vector<rg::Surface *>> animations;
    std::string status = "down_idle";
    std::string animation_status = "_idle";
    float frame_index = 0.0f;

    unsigned int tool_index = 0;
    unsigned int seed_index = 0;

    std::map<std::string, rg::Timer> timers;

    rg::SpriteGroup *collisionSprites = nullptr;
    rg::SpriteGroup *treeSprites = nullptr;

    rl::Vector2 target_pos{};
};
