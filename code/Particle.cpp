#include "Particle.h"

Particle::Particle(
        const Vector2 pos, Surface *surf, const std::vector<SpriteGroup *> &groups, const unsigned int z,
        const float duration)
    : GenericSprite(pos, surf, groups, z), duration(duration)
{
    start_time = GetFrameTime();

    auto *mask_surf = new Surface(image->Texture()->width, image->Texture()->height);
    Image mask = ImageFromChannel(LoadImageFromTexture(*image->Texture()), 3);
    ImageAlphaMask(&mask, mask);
    Texture texture_mask = LoadTextureFromImage(mask);
    mask_surf->Blit(&texture_mask);
    UnloadImage(mask);
    UnloadTexture(texture_mask);
}

void Particle::Update(float deltaTime)
{
    const float current_time = GetFrameTime();
    if (current_time - start_time > duration)
    {
        Kill();
    }
}
