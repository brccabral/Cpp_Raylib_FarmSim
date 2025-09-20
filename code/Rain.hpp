#pragma once
#include "CameraGroup.hpp"
#include "Sprites/Drop.hpp"


class Rain
{
public:

    Rain() = default;
    explicit Rain(CameraGroup *all_sprites);
    void Update();

private:

    void CreateFloor();
    void CreateDrops();

    CameraGroup *all_sprites = nullptr;
    std::vector<rg::Surface> rain_drops{};
    std::vector<rg::Surface> rain_floor{};
    unsigned int ground_w{};
    unsigned int ground_h{};

    std::vector<Drop> drops_sprites_;
};
