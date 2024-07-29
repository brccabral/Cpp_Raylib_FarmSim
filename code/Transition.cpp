#include "Transition.h"

#include "Settings.h"

Transition::Transition(const std::function<void()> &reset, Player *player)
    : reset(reset), player(player)
{
    display_surface = rg::display::GetSurface();

    image = new rg::Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
}

Transition::~Transition()
{
    delete image;
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

    image->Fill({(unsigned char) color, (unsigned char) color, (unsigned char) color, 255});
    display_surface->Blit(image, {}, rl::BLEND_MULTIPLIED);
}
