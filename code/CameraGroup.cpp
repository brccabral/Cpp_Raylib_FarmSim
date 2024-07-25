#include "CameraGroup.h"
#include "Settings.h"


CameraGroup::CameraGroup()
{
    display_surface = rg::display::GetSurface();
}

void CameraGroup::CustomDraw(const Player *player)
{
    offset = rg::GetRectCenter(player->rect);
    offset.x -= SCREEN_WIDTH / 2.0f;
    offset.y -= SCREEN_HEIGHT / 2.0f;

    // stable_sort keeps original order in case of equality
    std::stable_sort(
            sprites.begin(), sprites.end(),
            [](const rg::SimpleSprite *l, const rg::SimpleSprite *r)
            {
                const float yl = GetRectCenter(l->rect).y;
                const float yr = GetRectCenter(r->rect).y;
                return yl < yr;
            });
    for (const auto &[layer, order]: LAYERS)
    {
        for (const auto *sprite: sprites)
        {
            if (sprite->z == order)
            {
                rg::RectangleU offset_rect = sprite->rect;
                offset_rect.pos -= offset;

                display_surface->Blit(sprite->image, offset_rect.pos);

                // debug
#ifdef SHOW_HITBOX
                if (sprite == player)
                {
                    Vector2 target_pos = GetRectCenter(offset_rect) + PLAYER_TOOL_OFFSET[player->direction_status];
                    rg::DrawCirc(display_surface, BLUE, target_pos, 5);
                }
#endif
            }
        }
    }
}
