#include "Interaction.h"

#include <utility>

Interaction::Interaction(
        const rg::math::Vector2 pos, const rg::math::Vector2 size,
        const std::vector<rg::sprite::Group *> &groups, std::string name)
    : GenericSprite(pos, rg::Surface::Create((int) size.x, (int) size.y), groups),
      name(std::move(name))
{}
