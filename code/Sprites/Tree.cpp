#include <utility>
#include "Tree.h"


Tree::Tree(const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, std::string name)
    : GenericSprite(pos, surf, groups), name_(std::move(name))
{
    apple_pos = APPLE_POS[name_];
    CreateFruit();
}

Tree::~Tree()
{
    apple_sprites.DeleteAll();
}

void Tree::LeaveOtherGroups(const SpriteGroup *sprite_group)
{
    // if there is any apple in this tree, make sure to leave all
    // groups together with the tree, before the tree is deleted
    for (auto *sprite: apple_sprites.sprites)
    {
        sprite->LeaveOtherGroups(sprite_group);
    }
    GenericSprite::LeaveOtherGroups(sprite_group);
}

void Tree::CreateFruit()
{
    for (const auto position: apple_pos)
    {
        if (GetRandomValue(0, 9) < 2) // 20%
        {
            Surface *apple_surf = Surface::Load("resources/graphics/fruit/apple.png");
            const Vector2 pos = rect.pos + position;
            new GenericSprite(pos, apple_surf, {&apple_sprites, groups[0]}, LAYERS["fruit"]);
        }
    }
}

void Tree::Damage()
{
    // damaging tree
    health -= 1;

    // remove an apple
    if (!apple_sprites.sprites.empty())
    {
        const int random_apple = GetRandomValue(0, apple_sprites.sprites.size() - 1); // GetRandomValue includes `max`
        apple_sprites.sprites[random_apple]->Kill();
    }
}
