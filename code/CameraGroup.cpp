#include <algorithm>
#include "CameraGroup.hpp"
#include "Settings.hpp"


void CameraGroup::CustomDraw(const Player *player)
{
    offset = player->rect.center();
    offset.x -= SCREEN_WIDTH / 2.0f;
    offset.y -= SCREEN_HEIGHT / 2.0f;

    // stable_sort keeps original order in case of equality
    auto sorted = Sprites();
    std::ranges::stable_sort(
            sorted,
            [](const rg::sprite::Sprite *l, const rg::sprite::Sprite *r)
            {
                const float yl = l->rect.centery();
                const float yr = r->rect.centery();
                return yl < yr;
            });

    auto screen_pos = rg::Rect{0.0f, 0.0f, SCREEN_WIDTH * 1.02f, SCREEN_HEIGHT * 1.02f};
    screen_pos.center(player->rect.center());

    for (const auto &order: Settings::GetInstance().LAYERS | std::views::values)
    {
        for (const auto *sprite: sorted)
        {
            if (!screen_pos.colliderect(sprite->rect))
            {
                continue;
            }
            if (sprite->z == order)
            {
                rg::Rect offset_rect = sprite->rect;
                offset_rect -= offset;

                display_surface->Blit(sprite->image, offset_rect);

                // debug
#ifdef SHOW_HITBOX
                if (sprite == player)
                {
                    const rg::math::Vector2 target_pos =
                            offset_rect.center() + PLAYER_TOOL_OFFSET[player->direction_status];
                    rg::draw::circle(display_surface, rl::BLUE, target_pos, 5);
                }
#endif
            }
        }
    }
}
