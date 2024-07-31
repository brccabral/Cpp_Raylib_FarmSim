#include "Tree.h"
#include "Particle.h"


Tree::Tree(
        const rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::Group *> &groups,
        const char *name, const std::function<void(const std::string &item)> &player_add,
        rg::mixer::Sound *axe_sound)
    : GenericSprite(pos, surf, groups), name_(name), player_add(player_add), axe_sound(axe_sound)
{
    apple_pos = APPLE_POS[name_];
    CreateFruit();

    const std::string path = "resources/graphics/stumps/" + name_ + ".png";
    stump_surf = rg::Surface::Load(path.c_str());

#ifdef SHOW_HITBOX
    const rg::Rect rd = {0, 0, rect.size};
    rg::draw::rect(image, rl::RED, rd, 2);
    const rg::Rect hd =
            rd.inflate(-rect.width * 0.2f, -rect.height * 0.75f).midbottom(rd.midbottom());
    rg::draw::rect(image, rl::GREEN, hd, 2);
#endif
}

Tree::~Tree()
{
    if (alive)
    {
        delete stump_surf;
    }
}

void Tree::CreateFruit()
{
    if (!alive)
    {
        return;
    }
    for (const auto position: apple_pos)
    {
        if (rl::GetRandomValue(0, 9) < 2) // 20%
        {
            // apple_surf is deleted in apple.~Sprite()
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
        const rl::Vector2 oldMidBottom = rect.midbottom();
        rect = image->GetRect();
        rect.midbottom(oldMidBottom);
        hitbox = rect.inflate(-10, -rect.height * 0.6f);
        hitbox.midbottom(rect.midbottom());
        alive = false;
        player_add("wood");

#ifdef SHOW_HITBOX
        const rg::Rect rd = {0, 0, rect.size};
        rg::draw::rect(image, rl::RED, rd, 2);
        const rg::Rect hd = rd.inflate(-10, -rect.height * 0.6f).midbottom(rd.midbottom());
        rg::draw::rect(image, rl::GREEN, hd, 2);
#endif
    }
}

void Tree::Damage()
{
    // damaging tree
    health -= 1;

    // play sound
    axe_sound->Play();

    const auto apples = apple_sprites.Sprites();
    // remove an apple
    if (!apples.empty())
    {
        const int random_apple =
                rl::GetRandomValue(0, apples.size() - 1); // GetRandomValue includes `max`
        const auto apple = apples[random_apple];
        new Particle(apple->rect.pos, apple->image, {groups[0]}, LAYERS["fruit"]);
        player_add("apple");

        apple->Kill(true);
    }
}

void Tree::Update(float deltaTime)
{
    if (alive)
    {
        CheckDeath();
    }
}
