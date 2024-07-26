#pragma once
#include <raylib_utils.h>


class SoilLayer
{
public:

    explicit SoilLayer(rg::sprite::Group *all_sprites);
    ~SoilLayer();

    void GetHit(rl::Vector2 point);

private:

    void CreateSoilGrid();
    void CreateHitRects();
    void CreateSoilTiles();
    static bool IsFarmable(std::vector<std::string> cell);
    static bool IsHit(std::vector<std::string> cell);

    rg::sprite::Group *all_sprites = nullptr;
    rg::sprite::Group soil_sprites{};

    std::map<std::string, rg::Surface *> soil_surfs{};

    std::vector<std::vector<std::vector<std::string>>> grid;
    std::vector<rg::RectangleU> hit_rects{};
};
