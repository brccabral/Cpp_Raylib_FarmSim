#pragma once
#include <map>
#include <raylib_utils.h>
#include <string>


class Player : public SimpleSprite
{
public:

    Player(Vector2 pos, SpriteGroup *group);
    ~Player() override;
    void Update(float deltaTime) override;

    std::vector<std::string> tools = {"hoe", "axe", "water"};
    std::string selected_tool = tools[tool_index];

    std::vector<std::string> seeds = {"corn", "tomato"};
    std::string selected_seed = seeds[seed_index];

private:

    void Move(float dt);
    void ImportAssets();
    void Input();
    void Animate(float dt);
    void UpdateStatus();
    void UseTool();
    void UseSeed();

    Vector2 direction{};
    float speed = 200.0f;

    std::map<std::string, std::vector<Surface *>> animations;
    std::string status = "down_idle";
    std::string direction_status = "down";
    std::string animation_status = "_idle";
    float frame_index = 0.0f;

    unsigned int tool_index = 0;

    unsigned int seed_index = 0;

    std::map<std::string, Timer> timers;
};
