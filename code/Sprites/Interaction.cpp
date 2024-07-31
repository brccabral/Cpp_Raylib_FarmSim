#include "Interaction.h"

#include <utility>

Interaction::Interaction(
        const rg::math::Vector2 pos, const rg::math::Vector2 size,
        const std::vector<rg::sprite::Group *> &groups, std::string name)
    : GenericSprite(pos, nullptr, groups), name(std::move(name))
{
    const auto surf = new rg::Surface(size.x, size.y);
    InitImage(pos, surf);
}
