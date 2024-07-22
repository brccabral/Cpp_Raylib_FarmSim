#include "CameraGroup.h"
#include "Settings.h"


void CameraGroup::CustomDraw(const Player *player)
{
    offset = GetRectCenter(player->rect);
    offset.x -= SCREEN_WIDTH / 2.0f;
    offset.y -= SCREEN_HEIGHT / 2.0f;

    std::sort(
            sprites.begin(), sprites.end(),
            [](const SimpleSprite *l, const SimpleSprite *r)
            {
                const float yl = GetRectCenter(l->rect).y;
                const float yr = GetRectCenter(r->rect).y;
                return yl < yr;
            });
    for (unsigned int order = 0; order < LAYERS_ORDER.size(); ++order)
    {
        for (const auto *sprite: sprites)
        {
            if (sprite->z == order)
            {
                RectangleU offset_rect = sprite->rect;
                offset_rect.pos -= offset;

                display_surface->Blit(sprite->image, offset_rect.pos);
            }
        }
    }
}
