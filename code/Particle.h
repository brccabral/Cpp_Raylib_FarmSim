#pragma once
#include "Sprites/GenericSprite.h"


class Particle : public GenericSprite
{
public:

    // Quickly shows an image on screen and self destroys
    // duration = in seconds
    Particle(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups, unsigned int z,
            float duration = 0.2f);
    void Update(float deltaTime) override;

private:

    float start_time = 0;
    float duration = 0;
};
