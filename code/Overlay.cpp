#include "Overlay.h"

#include "Settings.h"

Overlay::Overlay(Player *player) : player(player)
{
    for (auto &tool: player->tools)
    {
        std::string path = "resources/graphics/overlay/" + tool + ".png";
        tools_surfaces[tool] = Surface::Load(path.c_str());
    }
    for (auto &seed: player->seeds)
    {
        std::string path = "resources/graphics/overlay/" + seed + ".png";
        seeds_surfaces[seed] = Surface::Load(path.c_str());
    }
}

Overlay::~Overlay()
{
    for (auto &[key, tool]: tools_surfaces)
    {
        delete tool;
    }
    for (auto &[key, seed]: seeds_surfaces)
    {
        delete seed;
    }
}

void Overlay::Display()
{
    auto *tool_surf = tools_surfaces[player->selected_tool];
    auto tool_rect = tool_surf->GetRect();
    RectToMidBottom(tool_rect, OVERLAY_POSITIONS["tool"]);
    display_surface->Blit(tool_surf, tool_rect.pos);

    auto *seed_surf = seeds_surfaces[player->selected_seed];
    auto seed_rect = seed_surf->GetRect();
    RectToMidBottom(seed_rect, OVERLAY_POSITIONS["seed"]);
    display_surface->Blit(seed_surf, seed_rect.pos);
}
