#include "Overlay.h"
#include "Settings.h"


Overlay::Overlay(const std::shared_ptr<Player> &player) : player(player)
{
    for (auto &tool: player->tools)
    {
        std::string path = "resources/graphics/overlay/" + tool + ".png";
        tools_surfaces[tool] = rg::image::Load(path.c_str());
    }
    for (auto &seed: player->seeds)
    {
        std::string path = "resources/graphics/overlay/" + seed + ".png";
        seeds_surfaces[seed] = rg::image::Load(path.c_str());
    }
}

void Overlay::Display()
{
    const auto tool_surf = tools_surfaces[player->selected_tool];
    auto tool_rect = tool_surf->GetRect();
    tool_rect.midbottom(OVERLAY_POSITIONS["tool"]);
    display_surface->Blit(tool_surf, tool_rect.pos);

    const auto seed_surf = seeds_surfaces[player->selected_seed];
    auto seed_rect = seed_surf->GetRect();
    seed_rect.midbottom(OVERLAY_POSITIONS["seed"]);
    display_surface->Blit(seed_surf, seed_rect.pos);
}
