#include "CameraGroup.h"

void CameraGroup::CustomDraw()
{
    for (const auto *sprite: sprites)
    {
        display_surface->Blit(sprite->image, sprite->rect.pos);
    }
}
