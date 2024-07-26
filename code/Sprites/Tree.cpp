#include "Tree.h"
#include "Particle.h"


Tree::Tree(
        const rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups, const char *name,
        const std::function<void(const std::string &item)> &player_add)
    : GenericSprite(pos, surf, groups), name_(name), player_add(player_add)
{
    apple_pos = APPLE_POS[name_];
    CreateFruit();

    const std::string path = "resources/graphics/stumps/" + name_ + ".png";
    stump_surf = rg::Surface::Load(path.c_str());

#ifdef SHOW_HITBOX
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
    if (alive)
    {
        delete stump_surf;
    }
}

void Tree::LeaveOtherGroups(const rg::sprite::Group *sprite_group)
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
        if (rl::GetRandomValue(0, 9) < 2) // 20%
        {
            rg::Surface *apple_surf = rg::Surface::Load("resources/graphics/fruit/apple.png");
            const rl::Vector2 pos = rect.pos + position;
            new GenericSprite(pos, apple_surf, {&apple_sprites, groups[0]}, LAYERS["fruit"]);
        }
    }
}

void Tree::CheckDeath()
{
    if (health <= 0)
    {
        new Particle(rect.pos, image, {groups[0]}, LAYERS["fruit"], 0.3);
        delete image;
        image = stump_surf;
        const rl::Vector2 oldMidBottom = GetRectMidBottom(rect);
        rect = image->GetRect();
        RectToMidBottom(rect, oldMidBottom);
        hitbox = rect;
        RectInflate(hitbox, -10, -rect.height * 0.6f);
        RectToMidBottom(hitbox, GetRectMidBottom(rect));
        alive = false;
        player_add("wood");

#ifdef SHOW_HITBOX
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
        const int random_apple =
                rl::GetRandomValue(0, apple_sprites.sprites.size() - 1); // GetRandomValue includes `max`
        const auto apple = apple_sprites.sprites[random_apple];
        new Particle(apple->rect.pos, apple->image, {groups[0]}, LAYERS["fruit"]);
        player_add("apple");
        apple->Kill();
    }
}

void Tree::Update(float deltaTime)
{
    if (alive)
    {
        CheckDeath();
    }
}
