#pragma once
#include "CameraGroup.h"


class Rain : public rg::sprite::SpriteOwner
{
public:

    explicit Rain(CameraGroup *all_sprites);
    ~Rain();
    void Update();

private:

    void CreateFloor();
    void CreateDrops();

    CameraGroup *all_sprites = nullptr;
    std::vector<rg::Surface *> rain_drops{};
    std::vector<rg::Surface *> rain_floor{};
    unsigned int ground_w;
    unsigned int ground_h;
};
