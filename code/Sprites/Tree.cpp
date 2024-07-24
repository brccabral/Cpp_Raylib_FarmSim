#include <utility>
#include "Tree.h"


Tree::Tree(const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, std::string name)
    : GenericSprite(pos, surf, groups), name_(std::move(name))
{
    apple_pos = APPLE_POS[name_];
    CreateFruit();

    const std::string path = "resources/graphics/stumps/" + name_ + ".png";
    stump_surf = Surface::Load(path.c_str());

#ifndef NDEBUG
    const RectangleU rd = {0, 0, rect.size};
    rg::DrawRect(image, RED, rd, 2);
    RectangleU hd = rd;
    RectInflate(hd, -rect.width * 0.2f, -rect.height * 0.75f);
    RectToMidBottom(hd, GetRectMidBottom(rd));
    rg::DrawRect(image, GREEN, hd, 2);
#endif
}

Tree::~Tree()
{
    apple_sprites.DeleteAll();
    if (alive)
    {
        delete stump_surf;
    }
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

void Tree::CheckDeath()
{
    if (health <= 0)
    {
        delete image;
        image = stump_surf;
        const Vector2 oldMidBottom = GetRectMidBottom(rect);
        rect = image->GetRect();
        RectToMidBottom(rect, oldMidBottom);
        hitbox = rect;
        RectInflate(hitbox, -10, -rect.height * 0.6f);
        RectToMidBottom(hitbox, GetRectMidBottom(rect));
        alive = false;

#ifndef NDEBUG
        const RectangleU rd = {0, 0, rect.size};
        rg::DrawRect(image, RED, rd, 2);
        RectangleU hd = rd;
        RectInflate(hd, -10, -rect.height * 0.6f);
        RectToMidBottom(hd, GetRectMidBottom(rd));
        rg::DrawRect(image, GREEN, hd, 2);
#endif
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

void Tree::Update(float deltaTime)
{
    if (alive)
    {
        CheckDeath();
    }
}
