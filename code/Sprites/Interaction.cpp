#include "Interaction.h"

#include <utility>

Interaction::Interaction(
        const rg::math::Vector2 pos, const rg::math::Vector2 size,
        const std::vector<rg::sprite::Group *> &groups, rg::sprite::SpriteOwner *owner, std::string name)
    : GenericSprite(pos, rg::Surface::Create((int) size.x, (int) size.y), groups, owner),
      name(std::move(name))
{}
