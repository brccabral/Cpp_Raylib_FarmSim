#include <utility>
#include "Interaction.hpp"


Interaction::Interaction(
        const rg::math::Vector2 pos, const rg::math::Vector2 size, std::string name)
    : GenericSprite(pos, &surface),
      name(std::move(name)), surface((int) size.x, (int) size.y)
{
}
