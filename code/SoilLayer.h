#pragma once
#include <rygame.h>


class SoilLayer
{
public:

    explicit SoilLayer(rg::sprite::Group *all_sprites);
    ~SoilLayer();

    // Check if point is in a hittable tile, if so, adds a SoilTile to it
    void GetHit(rl::Vector2 point);
    // Adds WaterTile to an existing SoilTile
    void Water(rl::Vector2 point);
    // Remove all WaterTile, called when player goes to sleep (reset Level)
    void RemoveWater();
    // When it rains, all available soil will be watered
    void WaterAll();

    bool raining{};

private:

    void CreateSoilGrid();
    void CreateHitRects();
    void CreateSoilTiles();
    void CreateWaterTile(rl::Vector2 pos);
    static bool IsFarmable(std::vector<char> cell);
    static bool IsHit(std::vector<char> cell);
    static bool IsWater(std::vector<char> cell);

    rg::sprite::Group *all_sprites = nullptr;
    rg::sprite::Group soil_sprites{};
    rg::sprite::Group water_sprites{};

    std::map<std::string, rg::Surface *> soil_surfs{};
    std::vector<rg::Surface *> water_surfs{};

    std::vector<std::vector<std::vector<char>>> grid;
    std::vector<rg::RectangleU> hit_rects{};
};
