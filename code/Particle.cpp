#include "Particle.h"

Particle::Particle(
        const rl::Vector2 pos, rg::Surface *surf, const std::vector<rg::sprite::SpriteGroup *> &groups,
        const unsigned int z, const float duration)
    : GenericSprite(pos, surf, groups, z), duration(duration)
{
    start_time = rl::GetFrameTime();

    auto *mask_surf = new rg::Surface(image->Texture()->width, image->Texture()->height);
    rl::Image mask = ImageFromChannel(LoadImageFromTexture(*image->Texture()), 3);
    ImageAlphaMask(&mask, mask);
    rl::Texture texture_mask = LoadTextureFromImage(mask);
    mask_surf->Blit(&texture_mask);
    UnloadImage(mask);
    UnloadTexture(texture_mask);
}

void Particle::Update(float deltaTime)
{
    const float current_time = rl::GetFrameTime();
    if (current_time - start_time > duration)
    {
        Kill();
    }
}
