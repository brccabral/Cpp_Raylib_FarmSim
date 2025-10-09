#include "Transition.hpp"


Transition::Transition(const std::function<void()> &reset, Player *player)
    : reset(reset), player(player)
{
}

void Transition::Play()
{
    color += speed;

    if (color <= 0)
    {
        speed *= -1;
        color = 0;
        reset();
    }
    else if (color > 255)
    {
        speed *= -1;
        color = 255;
        player->sleep = false;
    }

    image.Fill({(unsigned char) color, (unsigned char) color, (unsigned char) color, 255});
    display_surface->Blit(&image, rg::math::Vector2<float>{}, image.atlas_rect, rl::BLEND_MULTIPLIED);
}
