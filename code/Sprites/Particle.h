#pragma once
#include "GenericSprite.h"


class Particle : public GenericSprite
{
public:

    // Quickly shows an image on screen and self destroys
    // duration = in seconds
    Particle(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups, unsigned int z,
            double duration = 0.2);
    void Update(float deltaTime) override;

private:

    double start_time = 0;
    double duration = 0;
};
