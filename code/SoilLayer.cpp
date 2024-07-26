#include "SoilLayer.h"

#include "Settings.h"

SoilLayer::SoilLayer(rg::sprite::Group *all_sprites, rl::tmx_map *map) : all_sprites(all_sprites), map(map)
{
    soil_surf = rg::Surface::Load("resources/graphics/soil/o.png");

    CreateSoilGrid();
}

SoilLayer::~SoilLayer()
{
    delete soil_surf;
}

void SoilLayer::CreateSoilGrid()
{
    const rg::Surface *ground = rg::Surface::Load("resources/graphics/world/ground.png");
    unsigned int h_tiles = ground->GetRect().width / TILE_SIZE;
    unsigned int v_tiles = ground->GetRect().height / TILE_SIZE;

    for (int row = 0; row < v_tiles; ++row)
    {
        grid.emplace_back();
        for (int col = 0; col < h_tiles; ++col)
        {
            grid[row].emplace_back();
        }
    }

    const rl::tmx_layer *farmableLayer = tmx_find_layer_by_name(map, "Farmable");
    auto tiles = rg::GetTMXTiles(map, farmableLayer);
    for (auto [position, surface]: tiles)
    {
        const unsigned int x = position.x / TILE_SIZE;
        const unsigned int y = position.y / TILE_SIZE;
        grid[y][x].emplace_back("F");
        delete surface;
    }

    delete ground;
}
