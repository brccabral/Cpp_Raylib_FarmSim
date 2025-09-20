#include <algorithm>
#include <memory>

#include "SoilLayer.hpp"
#include "Settings.hpp"
#include "Sprites/Plant.hpp"
#include "Sprites/SoilTile.hpp"
#include "Sprites/WaterTile.hpp"


SoilLayer::SoilLayer(rg::sprite::Group *all_sprites, rg::sprite::Group *collisionSprites)
    : all_sprites(all_sprites), collisionSprites(collisionSprites)
{
    soil_surfs = rg::image::ImportFolderDict("resources/graphics/soil");
    water_surfs = rg::image::ImportFolder("resources/graphics/soil_water");

    CreateSoilGrid();
    CreateHitRects();
}

void SoilLayer::GetHit(const rg::math::Vector2 point)
{
    for (const auto rect: hit_rects)
    {
        if (rect.collidepoint(point))
        {
            const unsigned int x = rect.x / TILE_SIZE;
            const unsigned int y = rect.y / TILE_SIZE;
            if (IsFarmable(grid[y][x]))
            {
                grid[y][x].emplace_back('X');
                CreateSoilTiles();
            }
        }
    }
}

void SoilLayer::AddWater(const rg::math::Vector2 point)
{
    // only if it is a SoilSprite (is in group soil_sprites)
    for (const auto *sprite: soil_sprites.Sprites())
    {
        if (sprite->rect.collidepoint(point))
        {
            const unsigned int x = sprite->rect.x / TILE_SIZE;
            const unsigned int y = sprite->rect.y / TILE_SIZE;
            grid[y][x].emplace_back('W');

            CreateWaterTile(sprite->rect.pos);
        }
    }
}

void SoilLayer::RemoveAllWater()
{
    // destroy all water sprites
    for (auto *water: water_sprites.Sprites())
    {
        water->Kill();
    }

    // clean up the grid
    for (auto &row: grid)
    {
        for (auto &cell: row)
        {
            if (IsWater(cell))
            {
                cell.erase(std::remove(cell.begin(), cell.end(), 'W'), cell.end());
            }
        }
    }
}

void SoilLayer::RemovePlant(const rg::math::Vector2 pos)
{
    const unsigned int x = pos.x / TILE_SIZE;
    const unsigned int y = pos.y / TILE_SIZE;
    auto *cell = &grid[y][x];
    cell->erase(std::remove(cell->begin(), cell->end(), 'P'), cell->end());
}

void SoilLayer::WaterAll()
{
    for (unsigned int index_row = 0; index_row < grid.size(); ++index_row)
    {
        for (unsigned int index_col = 0; index_col < grid[index_row].size(); ++index_col)
        {
            auto &cell = grid[index_row][index_col];
            if (IsHit(cell) && !IsWater(cell))
            {
                cell.emplace_back('W');
                const float x = index_col * TILE_SIZE;
                const float y = index_row * TILE_SIZE;
                CreateWaterTile({x, y});
            }
        }
    }
}

bool SoilLayer::PlantSeed(const rg::math::Vector2 pos, const std::string &seed)
{
    for (const auto *soil_sprite: soil_sprites.Sprites())
    {
        if (soil_sprite->rect.collidepoint(pos))
        {
            const unsigned int x = soil_sprite->rect.x / TILE_SIZE;
            const unsigned int y = soil_sprite->rect.y / TILE_SIZE;

            if (!IsPlant(grid[y][x]))
            {
                grid[y][x].emplace_back('P');
                plants_sprites_.emplace_back(
                        soil_sprite->rect.midbottom(), seed, [this](
                        const rg::math::Vector2 target)
                        {
                            return this->CheckWatered(target);
                        });
                plants_sprites_.back().add({all_sprites, &plant_sprites, collisionSprites});
                return true;
            }
        }
    }
    return false;
}

bool SoilLayer::CheckWatered(const rg::math::Vector2 pos) const
{
    const unsigned int x = pos.x / TILE_SIZE;
    const unsigned int y = pos.y / TILE_SIZE;
    return IsWater(grid[y][x]);
}

void SoilLayer::CreateSoilGrid()
{
    const auto ground = rg::image::Load("resources/graphics/world/ground.png");
    const unsigned int h_tiles = ground.GetRect().width / TILE_SIZE;
    const unsigned int v_tiles = ground.GetRect().height / TILE_SIZE;

    grid.resize(v_tiles);
    soil_tiles_sprites_.resize(v_tiles);
    waters_sprites_.resize(v_tiles);
    for (unsigned int row = 0; row < v_tiles; ++row)
    {
        grid[row].resize(h_tiles);
        soil_tiles_sprites_[row].reserve(h_tiles);
        waters_sprites_[row].reserve(h_tiles);
    }

    rl::tmx_map *map = rl::LoadTMX("resources/data/map.tmx");

    const rl::tmx_layer *farmableLayer = tmx_find_layer_by_name(map, "Farmable");
    auto tiles = rg::tmx::GetTMXTiles(map, farmableLayer);
    for (auto &[position, gid]: tiles)
    {
        const unsigned int x = position.x / TILE_SIZE;
        const unsigned int y = position.y / TILE_SIZE;
        grid[y][x].emplace_back('F');
    }

    UnloadTMX(map);
}

void SoilLayer::CreateHitRects()
{
    hit_rects.clear();
    for (unsigned int index_row = 0; index_row < grid.size(); ++index_row)
    {
        for (unsigned int index_col = 0; index_col < grid[index_row].size(); ++index_col)
        {
            if (IsFarmable(grid[index_row][index_col]))
            {
                const unsigned int x = index_col * TILE_SIZE;
                const unsigned int y = index_row * TILE_SIZE;
                rg::Rect rect = {(float) x, (float) y, (float) TILE_SIZE, (float) TILE_SIZE};
                hit_rects.push_back(rect);
            }
        }
    }
}

void SoilLayer::CreateSoilTiles()
{
    soil_sprites.empty();
    for (unsigned int index_row = 0; index_row < grid.size(); ++index_row)
    {
        for (unsigned int index_col = 0; index_col < grid[index_row].size(); ++index_col)
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
                soil_tiles_sprites_[index_row][index_col] = SoilTile(
                        rg::math::Vector2{x, y}, &soil_surfs[tyle_type]);
                soil_tiles_sprites_[index_row][index_col].add({all_sprites, &soil_sprites});
                if (raining)
                {
                    CreateWaterTile({x, y});
                }
            }
        }
    }
}

void SoilLayer::CreateWaterTile(const rg::math::Vector2 &pos)
{
    const unsigned int random_water = rl::GetRandomValue(0, water_surfs.size() - 1);
    const int index_row = pos.y / TILE_SIZE;
    const int index_col = pos.x / TILE_SIZE;
    waters_sprites_[index_row][index_col] = WaterTile(pos, &water_surfs[random_water]);
    waters_sprites_[index_row][index_col].add({all_sprites, &water_sprites});
}

bool SoilLayer::IsFarmable(const std::vector<char> &cell)
{
    return std::find(cell.begin(), cell.end(), 'F') != cell.end();
}

bool SoilLayer::IsHit(const std::vector<char> &cell)
{
    return std::find(cell.begin(), cell.end(), 'X') != cell.end();
}

bool SoilLayer::IsWater(const std::vector<char> &cell)
{
    return std::find(cell.begin(), cell.end(), 'W') != cell.end();
}

bool SoilLayer::IsPlant(const std::vector<char> &cell)
{
    return std::find(cell.begin(), cell.end(), 'P') != cell.end();
}

void SoilLayer::UpdatePlants() const
{
    for (auto *sprite: plant_sprites.Sprites())
    {
        const auto plant = dynamic_cast<Plant *>(sprite);
        plant->Grow();
    }
}
