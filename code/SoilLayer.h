#pragma once
#include <rygame.h>


class SoilLayer
{
public:

    explicit SoilLayer(rg::sprite::Group *all_sprites, rg::sprite::Group *collisionSprites);
    ~SoilLayer();

    // Check if point is in a hittable tile, if so, adds a SoilTile to it
    void GetHit(rl::Vector2 point);
    // Adds WaterTile to an existing SoilTile
    void Water(rl::Vector2 point);
    // Remove all WaterTile, called when player goes to sleep (reset Level)
    void RemoveAllWater();
    // Remove Plant from position (during harvesting)
    void RemovePlant(rl::Vector2 pos);
    // When it rains, all available soil will be watered
    void WaterAll();
    // Plant a seed in an empty soil
    void PlantSeed(rl::Vector2 pos, const std::string &seed);
    // Check if position contains a watered soil
    [[nodiscard]] bool CheckWatered(rl::Vector2 pos) const;
    // Update all plants
    void UpdatePlants();

    bool raining{};
    rg::sprite::Group plant_sprites{};

private:

    void CreateSoilGrid();
    void CreateHitRects();
    void CreateSoilTiles();
    void CreateWaterTile(rl::Vector2 pos);
    static bool IsFarmable(const std::vector<char> &cell);
    static bool IsHit(const std::vector<char> &cell);
    static bool IsWater(const std::vector<char> &cell);
    static bool IsPlant(const std::vector<char> &cell);

    rg::sprite::Group *all_sprites = nullptr;
    rg::sprite::Group *collisionSprites = nullptr;
    rg::sprite::Group soil_sprites{};
    rg::sprite::Group water_sprites{};

    std::map<std::string, rg::Surface *> soil_surfs{};
    std::vector<rg::Surface *> water_surfs{};

    std::vector<std::vector<std::vector<char>>> grid;
    std::vector<rg::RectangleU> hit_rects{};
};
