#pragma once
#include <raylib_utils.h>


class SoilLayer
{
public:

    explicit SoilLayer(rg::sprite::Group *all_sprites, rl::tmx_map *map);
    ~SoilLayer();

private:

    void CreateSoilGrid();

    rg::sprite::Group *all_sprites = nullptr;
    rg::sprite::Group soil_sprites{};

    rg::Surface *soil_surf = nullptr;
    rl::tmx_map *map = nullptr;

    std::vector<std::vector<std::vector<std::string>>> grid;
};
