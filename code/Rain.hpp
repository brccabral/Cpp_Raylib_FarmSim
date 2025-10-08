#pragma once
#include "CameraGroup.hpp"
#include "Sprites/Drop.hpp"


class Rain
{
public:

    Rain() = default;
    explicit Rain(CameraGroup *all_sprites, unsigned int ground_width, unsigned int ground_height);
    void Update();

private:

    void CreateFloor();
    void CreateDrops();

    CameraGroup *all_sprites = nullptr;
    std::vector<rg::Surface> rain_drops{};
    std::vector<rg::Surface> rain_floor{};
    unsigned int ground_width{};
    unsigned int ground_height{};

    std::vector<Drop> drops_sprites_;
};
