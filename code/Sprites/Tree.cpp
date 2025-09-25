#include "Tree.hpp"
#include "Particle.hpp"


Tree::Tree(
        const rg::math::Vector2 pos, rg::Surface *surf, rg::Surface *apple_surf,
        rg::Surface *stump_surf, const char *name, CameraGroup *all_sprites,
        const std::function<void(const std::string &item)> &player_add)
    : GenericSprite(pos, surf), all_sprites(all_sprites), name_(name), stump_surf(stump_surf),
      apple_surf(apple_surf), player_add(player_add)
{
    apples_sprites_.resize(APPLE_POS[name_].size());
    particles_sprites_.resize(APPLE_POS[name_].size() + 1);

#ifdef SHOW_HITBOX
    const rg::Rect rd = {0, 0, rect.size};
    rg::draw::rect(image, rl::RED, rd, 2);
    const rg::Rect hd =
            rd.inflate(-rect.width * 0.2f, -rect.height * 0.75f).midbottom(rd.midbottom());
    rg::draw::rect(image, rl::GREEN, hd, 2);
#endif
}

void Tree::CreateFruit()
{
    if (!alive)
    {
        return;
    }
    int apple = 0;
    for (const auto &position: APPLE_POS[name_])
    {
        if (rl::GetRandomValue(0, 9) < 2) // 20%
        {
            const rg::math::Vector2 pos = rect.pos + position;
            apples_sprites_[apple] = GenericSprite(
                    pos, apple_surf,
                    LAYERS["fruit"]);
            apples_sprites_[apple].add({&apple_sprites, all_sprites}); // groups[0] is all_sprites
            ++apple;
        }
    }
}

void Tree::CheckDeath()
{
    if (health <= 0)
    {
        for (auto &ps: particles_sprites_)
        {
            if (!ps.is_alive)
            {
                ps = Particle(rect.pos, image, LAYERS["fruit"], 0.3);
                ps.add(groups[0]);
                break;
            }
        }
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

    const auto &apples = apple_sprites.Sprites();
    // remove an apple
    if (!apples.empty())
    {
        const int random_apple =
                rl::GetRandomValue(0, apples.size() - 1); // GetRandomValue includes `max`
        auto *apple = apples[random_apple];
        for (auto &ps: particles_sprites_)
        {
            if (!ps.is_alive)
            {
                ps = Particle(
                        apple->rect.pos, apple->image, LAYERS["fruit"]);
                ps.add(groups[0]);
                break;
            }
        }
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
