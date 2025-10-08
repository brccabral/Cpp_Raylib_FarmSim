#include "Plant.hpp"
#include "../Settings.hpp"


Plant::Plant(
        const rg::math::Vector2<float> pos, const std::string &plant_type,
        const std::function<bool(rg::math::Vector2<float> target)> &check_watered = nullptr)
    : GenericSprite(pos, nullptr, Settings::GetInstance().LAYERS["ground plant"]),
      plant_type(plant_type),
      check_watered(check_watered)
{
    const std::string path = "resources/graphics/fruit/" + plant_type;
    frames = rg::image::LoadFolderList(path.c_str());

    max_age = frames.size() - 1;
    grow_speed = Settings::GetInstance().GROW_SPEED[plant_type];

    if (!strcmp(plant_type.c_str(), "corn"))
    {
        y_offset = -16;
    }
    else
    {
        y_offset = -8;
    }
    image = &frames[int(age)];
    rect = image->GetRect().midbottom(pos);
    rect += {0.0f, y_offset};

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
        const rg::math::Vector2<float> oldCenter = rect.center();
        image = &frames[int(age)];
        rect = image->GetRect();
        rect.center(oldCenter);
        if (age >= 1)
        {
            z = Settings::GetInstance().LAYERS["main"];
            hitbox = rect.inflate(-26, -rect.height * 0.4);
        }
    }
}
