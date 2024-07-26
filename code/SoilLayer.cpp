#include "SoilLayer.h"

#include "Settings.h"
#include "Sprites/SoilTile.h"
#include "Sprites/WaterTile.h"

SoilLayer::SoilLayer(rg::sprite::Group *all_sprites) : all_sprites(all_sprites)
{
    soil_surfs = rg::assets::ImportFolderDict("resources/graphics/soil");
    water_surfs = rg::assets::ImportFolder("resources/graphics/soil_water");

    CreateSoilGrid();
    CreateHitRects();
}

SoilLayer::~SoilLayer()
{
    for (auto &[key, surf]: soil_surfs)
    {
        delete surf;
    }
    for (const auto *surf: water_surfs)
    {
        delete surf;
    }
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
                CreateSoilTiles();
            }
        }
    }
}

void SoilLayer::Water(const rl::Vector2 point)
{
    // only if it is a SoilSprite (is in group soil_sprites)
    for (const auto *sprite: soil_sprites.sprites)
    {
        if (CheckCollisionPointRec(point, sprite->rect.rectangle))
        {
            const unsigned int x = sprite->rect.x / TILE_SIZE;
            const unsigned int y = sprite->rect.y / TILE_SIZE;
            grid[y][x].emplace_back("W");

            const unsigned int random_water = rl::GetRandomValue(0, water_surfs.size() - 1);
            new WaterTile(
                    sprite->rect.pos, water_surfs[random_water], {all_sprites, &water_sprites});
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
        // ReSharper disable once CppDFADeletedPointer
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

void SoilLayer::CreateSoilTiles()
{
    soil_sprites.empty();
    for (int index_row = 0; index_row < grid.size(); ++index_row)
    {
        for (int index_col = 0; index_col < grid[index_row].size(); ++index_col)
        {
            if (IsHit(grid[index_row][index_col]))
            {
                // top, bottom, right, left
                const bool t = IsHit(grid[index_row - 1][index_col]);
                const bool b = IsHit(grid[index_row + 1][index_col]);
                const bool r = IsHit(grid[index_row][index_col + 1]);
                const bool l = IsHit(grid[index_row][index_col - 1]);

                std::string tyle_type = "o";

                // all sides
                if (t && b && r && l)
                {
                    tyle_type = "x";
                }
                // horizontal tiles only
                if (l && !t && !r && !b) // left only
                {
                    tyle_type = "r";
                }
                if (r && !t && !l && !b) // right only
                {
                    tyle_type = "l";
                }
                if (r && l && !t && !b) // left and right
                {
                    tyle_type = "lr";
                }

                // vertical tiles only
                if (t && !r && !l && !b) // top only
                {
                    tyle_type = "b";
                }
                if (b && !r && !l && !t) // bottom only
                {
                    tyle_type = "t";
                }
                if (b && t && !r && !l) // top and bottom
                {
                    tyle_type = "tb";
                }

                // corners
                if (l && b && !t && !r) // left and bottom
                {
                    tyle_type = "tr";
                }
                if (r && b && !t && !l) // right and bottom
                {
                    tyle_type = "tl";
                }
                if (l && t && !b && !r) // left and top
                {
                    tyle_type = "br";
                }
                if (r && t && !b && !l) // right and top
                {
                    tyle_type = "bl";
                }

                // T shapes
                if (t && b && r && !l) // T right
                {
                    tyle_type = "tbr";
                }
                if (t && b && l && !r) // T left
                {
                    tyle_type = "tbl";
                }
                if (l && r && t && !b) // T up
                {
                    tyle_type = "lrb";
                }
                if (l && r && b && !t) // T down
                {
                    tyle_type = "lrt";
                }

                const float x = index_col * TILE_SIZE;
                const float y = index_row * TILE_SIZE;
                // TODO: this is adding the same x,y to all_sprites
                new SoilTile({x, y}, soil_surfs[tyle_type], {all_sprites, &soil_sprites});
            }
        }
    }
}

bool SoilLayer::IsFarmable(std::vector<std::string> cell)
{
    return std::find(cell.begin(), cell.end(), "F") != cell.end();
}

bool SoilLayer::IsHit(std::vector<std::string> cell)
{
    return std::find(cell.begin(), cell.end(), "X") != cell.end();
}
