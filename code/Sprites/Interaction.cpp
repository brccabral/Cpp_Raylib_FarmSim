#include <utility>
#include "Interaction.hpp"


Interaction::Interaction(
        const rg::math::Vector2 pos, const rg::math::Vector2 size, std::string name)
    : GenericSprite(pos, new rg::Surface((int) size.x, (int) size.y)),
      name(std::move(name))
{
}
