#include "SoilLayer.h"

#include "Settings.h"

SoilLayer::SoilLayer(rg::sprite::Group *all_sprites) : all_sprites(all_sprites)
{
    soil_surf = rg::Surface::Load("resources/graphics/soil/o.png");

    CreateSoilGrid();
    CreateHitRects();
}

SoilLayer::~SoilLayer()
{
    delete soil_surf;
}

void SoilLayer::GetHit(const rl::Vector2 point)
{
    for (const auto rect: hit_rects)
    {
        if (CheckCollisionPointRec(point, rect.rectangle))
        {
            const unsigned int x = rect.x / TILE_SIZE;
            const unsigned int y = rect.y / TILE_SIZE;
            if (IsFarmable(grid[y][x]))
            {
                grid[y][x].emplace_back("X");
            }
        }
    }
}

void SoilLayer::CreateSoilGrid()
{
    const rg::Surface *ground = rg::Surface::Load("resources/graphics/world/ground.png");
    const unsigned int h_tiles = ground->GetRect().width / TILE_SIZE;
    const unsigned int v_tiles = ground->GetRect().height / TILE_SIZE;

    for (int row = 0; row < v_tiles; ++row)
    {
        grid.emplace_back();
        for (int col = 0; col < h_tiles; ++col)
        {
            grid[row].emplace_back();
        }
    }

    rl::tmx_map *map = rl::LoadTMX("resources/data/map.tmx");

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
    UnloadTMX(map);
}

void SoilLayer::CreateHitRects()
{
    hit_rects.clear();
    for (int index_row = 0; index_row < grid.size(); ++index_row)
    {
        for (int index_col = 0; index_col < grid[index_row].size(); ++index_col)
        {
            if (IsFarmable(grid[index_row][index_col]))
            {
                const unsigned int x = index_col * TILE_SIZE;
                const unsigned int y = index_row * TILE_SIZE;
                rg::RectangleU rect = {(float) x, (float) y, (float) TILE_SIZE, (float) TILE_SIZE};
                hit_rects.push_back(rect);
            }
        }
    }
}

bool SoilLayer::IsFarmable(std::vector<std::string> cell)
{
    return std::find(cell.begin(), cell.end(), "F") != cell.end();
}
