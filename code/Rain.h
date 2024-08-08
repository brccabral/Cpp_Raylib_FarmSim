#pragma once
#include "CameraGroup.h"


class Rain
{
public:

    explicit Rain(CameraGroup *all_sprites);
    void Update();

private:

    void CreateFloor();
    void CreateDrops();

    CameraGroup *all_sprites = nullptr;
    std::vector<std::shared_ptr<rg::Surface>> rain_drops{};
    std::vector<std::shared_ptr<rg::Surface>> rain_floor{};
    unsigned int ground_w;
    unsigned int ground_h;
};
