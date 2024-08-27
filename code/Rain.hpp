#pragma once
#include "CameraGroup.hpp"


class Rain
{
public:

    explicit Rain(CameraGroup *all_sprites);
    void Update();

private:

    void CreateFloor();
    void CreateDrops();

    CameraGroup *all_sprites = nullptr;
    std::vector<rg::Surface_Ptr> rain_drops{};
    std::vector<rg::Surface_Ptr> rain_floor{};
    unsigned int ground_w;
    unsigned int ground_h;
};
