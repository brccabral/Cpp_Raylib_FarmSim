#pragma once
#include <raylib_utils.h>


class Player : public SimpleSprite
{
public:

    Player(Vector2 pos, SpriteGroup *group);
    ~Player() override;
    void Input();
    void Update(float deltaTime) override;

private:

    void Move(float dt);
    Vector2 direction{};
    float speed = 200.0f;
};
