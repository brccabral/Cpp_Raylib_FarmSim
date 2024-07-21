#include "CameraGroup.h"
#include "Settings.h"


void CameraGroup::CustomDraw()
{
    for (auto &[key, order]: LAYERS)
    {
        for (const auto *sprite: sprites)
        {
            if (sprite->z == order)
            {
                display_surface->Blit(sprite->image, sprite->rect.pos);
            }
        }
    }
}
