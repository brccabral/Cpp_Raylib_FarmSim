#include "CameraGroup.hpp"
#include "Settings.hpp"


void CameraGroup::CustomDraw(const std::shared_ptr<Player> &player)
{
    offset = player->rect.center();
    offset.x -= SCREEN_WIDTH / 2.0f;
    offset.y -= SCREEN_HEIGHT / 2.0f;

    // stable_sort keeps original order in case of equality
    std::stable_sort(
            sprites.begin(), sprites.end(),
            [](const rg::sprite::Sprite_Ptr &l, const rg::sprite::Sprite_Ptr &r)
            {
                const float yl = l->rect.centery();
                const float yr = r->rect.centery();
                return yl < yr;
            });
    for (const auto &[layer, order]: LAYERS)
    {
        for (const auto &sprite: sprites)
        {
            if (sprite->z == order)
            {
                rg::Rect offset_rect = sprite->rect;
                offset_rect.pos -= offset;

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
