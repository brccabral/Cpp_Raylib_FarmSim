#include "Plant.h"

#include "../Settings.h"

Plant::Plant(
        const rl::Vector2 pos, const std::vector<rg::sprite::Group *> &groups,
        const std::string &plant_type)
    : Sprite(groups), plant_type(plant_type)
{
    const std::string path = "resources/graphics/fruit/" + plant_type;
    frames = rg::assets::ImportFolder(path.c_str());

    max_age = frames.size() - 1;
    grow_speed = GROW_SPEED[plant_type];

    if (!strcmp(plant_type.c_str(), "corn"))
    {
        y_offset = -16;
    }
    else
    {
        y_offset = -8;
    }
    image = frames[age];
    rect = image->GetRect();
    RectToMidBottom(rect, pos);
    rect.pos += {0, y_offset};

    z = LAYERS["ground plant"];
}

Plant::~Plant()
{
    for (const auto *surface: frames)
    {
        delete surface;
    }
    // avoid double delete in ~Sprite()
    image = nullptr;
}
