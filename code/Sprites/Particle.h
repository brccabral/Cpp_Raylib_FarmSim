#pragma once
#include "GenericSprite.h"


// Quickly shows an image on screen and self destroys
// duration = in seconds, default 0.2
// surf = the passed surface is replaced with a new one (mask), make sure
//        to delete the passed surface outside the Particle
class Particle : public GenericSprite
{
public:

    Particle(
            rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups,
            unsigned int z, double duration = 0.2);
    void Update(float deltaTime) override;

private:

    double start_time = 0;
    double duration = 0;
};
