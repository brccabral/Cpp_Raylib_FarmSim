#include "Plant.h"
#include "../Settings.h"


Plant::Plant(
        const rg::math::Vector2 pos, const std::string &plant_type,
        const std::function<bool(rg::math::Vector2 target)> &check_watered = nullptr)
    : GenericSprite(pos, nullptr, LAYERS["ground plant"]), plant_type(plant_type),
      check_watered(check_watered)
{
    const std::string path = "resources/graphics/fruit/" + plant_type;
    const auto plantsSurfaces = rg::image::ImportFolder(path.c_str());

    max_age = plantsSurfaces.size() - 1;
    grow_speed = GROW_SPEED[plant_type];

    if (!strcmp(plant_type.c_str(), "corn"))
    {
        y_offset = -16;
    }
    else
    {
        y_offset = -8;
    }
    image = rg::Frames::Merge(plantsSurfaces, 1, plantsSurfaces.size());
    rect = image->GetRect().midbottom(pos);
    rect.pos += {0, y_offset};

#ifdef SHOW_HITBOX
    for (const auto *surface: frames)
    {
        const rg::Rect rd = surface->GetRect();
        rg::draw::rect(surface, rl::RED, rd, 2);
        rg::Rect hd = rd.inflate(-26, -rd.height * 0.4);
        rg::draw::rect(surface, rl::GREEN, hd, 2);
    }
#endif
}

void Plant::Grow()
{
    if (check_watered(rect.center()))
    {
        age += grow_speed;
        if (age >= max_age)
        {
            age = max_age;
            harvestable = true;
        }
        const rg::math::Vector2 oldCenter = rect.center();
        std::dynamic_pointer_cast<rg::Frames>(image)->SetAtlas(int(age));
        rect = image->GetRect();
        rect.center(oldCenter);
        if (age >= 1)
        {
            z = LAYERS["main"];
            hitbox = rect.inflate(-26, -rect.height * 0.4);
        }
    }
}
