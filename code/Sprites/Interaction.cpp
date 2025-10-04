#include <utility>
#include "Interaction.hpp"


Interaction::Interaction(
        const rg::math::Vector2<float> pos, const rg::math::Vector2<float> size, std::string name)
    : GenericSprite(pos, new rg::Surface(size)),
      name(std::move(name))
{
}

Interaction::~Interaction()
{
    delete image;
}
