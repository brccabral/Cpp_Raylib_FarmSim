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
    static bool IsFarmable(std::vector<std::string> cell);

    rg::sprite::Group *all_sprites = nullptr;
    rg::sprite::Group soil_sprites{};

    rg::Surface *soil_surf = nullptr;

    std::vector<std::vector<std::vector<std::string>>> grid;
    std::vector<rg::RectangleU> hit_rects{};
};
