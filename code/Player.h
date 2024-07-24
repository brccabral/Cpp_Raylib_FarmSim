#pragma once
#include <map>
#include <string>
#include <raylib_utils.h>


class Player : public SimpleSprite
{
public:

    Player(Vector2 pos, SpriteGroup &group, SpriteGroup *collisionSprites);
    ~Player() override;
    void Update(float deltaTime) override;

    std::string direction_status = "down";

    std::vector<std::string> tools = {"hoe", "axe", "water"};
    std::string selected_tool = "hoe";

    std::vector<std::string> seeds = {"corn", "tomato"};
    std::string selected_seed = "corn";

    RectangleU hitbox{};

private:

    void Move(float dt);
    void ImportAssets();
    void Input();
    void Animate(float dt);
    void UpdateStatus();
    void UseTool();
    void UseSeed();
    void Collision(Axis axis);

    Vector2 direction{};
    float speed = 200.0f;

    std::map<std::string, std::vector<Surface *>> animations;
    std::string status = "down_idle";
    std::string animation_status = "_idle";
    float frame_index = 0.0f;

    unsigned int tool_index = 0;
    unsigned int seed_index = 0;

    std::map<std::string, Timer> timers;

    SpriteGroup *collisionSprites = nullptr;
};
