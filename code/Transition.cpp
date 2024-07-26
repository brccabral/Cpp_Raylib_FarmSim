#include "Transition.h"

#include "Settings.h"

Transition::Transition(const std::function<void()> &reset, Player *player) : reset(reset), player(player)
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
    transparency += speed;
    if (transparency <= 0)
    {
        speed *= -1;
        transparency = 0;
        reset(); // callback to reset the level
    }
    if (transparency >= 255)
    {
        speed *= -1;
        transparency = 255;
        player->sleep = false; // wake up the player
    }
    image->Fill(Fade(rl::BLACK, 1 - transparency / 255.0f));
    display_surface->Blit(image);
}
