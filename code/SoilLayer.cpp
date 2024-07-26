#include "SoilLayer.h"

#include "Settings.h"
#include "Sprites/Plant.h"
#include "Sprites/SoilTile.h"
#include "Sprites/WaterTile.h"

SoilLayer::SoilLayer(rg::sprite::Group *all_sprites, rg::sprite::Group *collisionSprites)
    : all_sprites(all_sprites), collisionSprites(collisionSprites)
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
                grid[y][x].emplace_back('X');
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
            grid[y][x].emplace_back('W');

            CreateWaterTile(sprite->rect.pos);
        }
    }
}

void SoilLayer::RemoveWater()
{
    // destroy all water sprites
    all_sprites->remove(water_sprites.sprites);
    water_sprites.empty();

    // clean up the grid
    for (auto &row: grid)
    {
        for (auto &cell: row)
        {
            if (IsWater(cell))
            {
                cell.erase(remove(cell.begin(), cell.end(), 'W'), cell.end());
            }
        }
    }
}

void SoilLayer::WaterAll()
{
    for (int index_row = 0; index_row < grid.size(); ++index_row)
    {
        for (int index_col = 0; index_col < grid[index_row].size(); ++index_col)
        {
            const auto cell = &grid[index_row][index_col];
            if (IsHit(*cell) && !IsWater(*cell))
            {
                cell->emplace_back('W');
                const float x = index_col * TILE_SIZE;
                const float y = index_row * TILE_SIZE;
                CreateWaterTile({x, y});
            }
        }
    }
}

void SoilLayer::PlantSeed(const rl::Vector2 pos, const std::string &seed)
{
    for (const auto *soil_sprite: soil_sprites.sprites)
    {
        if (CheckCollisionPointRec(pos, soil_sprite->rect.rectangle))
        {
            const unsigned int x = soil_sprite->rect.x / TILE_SIZE;
            const unsigned int y = soil_sprite->rect.y / TILE_SIZE;

            if (!IsPlant(grid[y][x]))
            {
                grid[y][x].emplace_back('P');
                new Plant(
                        GetRectMidBottom(soil_sprite->rect),
                        {all_sprites, &plant_sprites, collisionSprites}, seed,
                        [this](const rl::Vector2 target) { return this->CheckWatered(target); });
            }
        }
    }
}

bool SoilLayer::CheckWatered(const rl::Vector2 pos) const
{
    const unsigned int x = pos.x / TILE_SIZE;
    const unsigned int y = pos.y / TILE_SIZE;
    return IsWater(grid[y][x]);
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
    auto tiles = rg::tmx::GetTMXTiles(map, farmableLayer);
    for (auto [position, surface]: tiles)
    {
        const unsigned int x = position.x / TILE_SIZE;
        const unsigned int y = position.y / TILE_SIZE;
        grid[y][x].emplace_back('F');
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
                if (raining)
                {
                    CreateWaterTile({x, y});
                }
            }
        }
    }
}

void SoilLayer::CreateWaterTile(const rl::Vector2 pos)
{
    const unsigned int random_water = rl::GetRandomValue(0, water_surfs.size() - 1);
    new WaterTile(pos, water_surfs[random_water], {all_sprites, &water_sprites});
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

void SoilLayer::UpdatePlants()
{
    for (auto *sprite: plant_sprites.sprites)
    {
        const auto plant = (Plant *) sprite;
        plant->Grow();
    }
}
