#pragma once
#include <map>
#include <raylib_utils.h>
#include <string>


class Player : public SimpleSprite
{
public:

    Player(Vector2 pos, SpriteGroup *group);
    ~Player() override;
    void Input();
    void Update(float deltaTime) override;
    void Animate(float dt);

private:

    void Move(float dt);
    void ImportAssets();

    Vector2 direction{};
    float speed = 200.0f;

    std::map<std::string, std::vector<Surface *>> animations;
    std::string status = "down_idle";
    float frame_index = 0.0f;
};