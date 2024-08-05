#include "Tree.h"
#include "Particle.h"


Tree::Tree(
        const rg::math::Vector2 pos, rg::Surface *surf,
        const std::vector<rg::sprite::Group *> &groups, const char *name,
        const std::function<void(const std::string &item)> &player_add)
    : GenericSprite(pos, surf, groups), name_(name), player_add(player_add)
{
    apple_surf = rg::image::Load("resources/graphics/fruit/apple.png");
    apple_pos = APPLE_POS[name_];
    CreateFruit();

    const std::string path = "resources/graphics/stumps/" + name_ + ".png";
    stump_surf = rg::image::Load(path.c_str());

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
    // image is deleted in ~Sprite()
    if (alive)
    {
        delete stump_surf;
    }
    delete apple_surf;
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
            const rg::math::Vector2 pos = rect.pos + position;
            new GenericSprite(
                    pos, rg::Surface::Create(&apple_surf->render.texture),
                    {&apple_sprites, groups[0]}, LAYERS["fruit"]);
        }
    }
}

void Tree::CheckDeath()
{
    if (health <= 0)
    {
        new Particle(rect.pos, image, {groups[0]}, LAYERS["fruit"], 0.3);
        image = stump_surf;
        const rg::math::Vector2 oldMidBottom = rect.midbottom();
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
