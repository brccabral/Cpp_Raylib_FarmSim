#pragma once
#include <map>
#include <string>
#include <raylib_utils.h>


class Player : public rg::sprite::Sprite
{
public:

    Player(rl::Vector2 pos, rg::sprite::Group &group, rg::sprite::Group *collisionSprites,
           rg::sprite::Group *treeSprites);
    ~Player() override;
    void Update(float deltaTime) override;

    std::string direction_status = "down";

    std::vector<std::string> tools = {"hoe", "axe", "water"};
    std::string selected_tool = "hoe";

    std::vector<std::string> seeds = {"corn", "tomato"};
    std::string selected_seed = "corn";

    rg::RectangleU hitbox{};

    std::map<std::string, unsigned int> item_inventory = {
            {"wood", 0}, //
            {"apple", 0}, //
            {"corn", 0}, //
            {"tomato", 0} //
    };

private:

    void Move(float dt);
    void ImportAssets();
    void Input();
    void UpdateTimers();
    void Animate(float dt);
    void UpdateStatus();
    void UseTool();
    void UseSeed();
    void Collision(rg::Axis axis);
    void GetTargetPos();
    void SetStatus(const std::string &animation_status);

    rl::Vector2 direction{};
    float speed = 200.0f;

    std::map<std::string, std::vector<rg::Surface *>> animations;
    std::string status = "down_idle";
    float frame_index = 0.0f;

    unsigned int tool_index = 0;
    unsigned int seed_index = 0;

    std::map<std::string, rg::Timer> timers;

    rg::sprite::Group *collisionSprites = nullptr;
    rg::sprite::Group *treeSprites = nullptr;

    rl::Vector2 target_pos{};
};
