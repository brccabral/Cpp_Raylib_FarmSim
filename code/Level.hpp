#pragma once
#include "CameraGroup.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Overlay.hpp"
#include "Rain.hpp"
#include "Sky.hpp"
#include "SoilLayer.hpp"
#include "Transition.hpp"


class Level
{
public:

    Level();
    ~Level();
    void run(float dt);
    void Setup();

private:

    void PlayerAdd(const std::string &item) const;
    void Reset();
    void PlantCollision();
    void ToogleShop();

    std::shared_ptr<rg::Surface> display_surface = rg::display::GetSurface();

    CameraGroup all_sprites{};
    rg::sprite::Group collisionSprites{};
    rg::sprite::Group treeSprites{};
    rg::sprite::Group interactionSprites{};
    std::shared_ptr<Player> player = nullptr;
    std::shared_ptr<Overlay> overlay = nullptr;
    std::shared_ptr<Transition> transition = nullptr;
    std::shared_ptr<SoilLayer> soil_layer = nullptr;
    std::shared_ptr<Sky> sky = nullptr;
    std::shared_ptr<Rain> rain = nullptr;
    std::shared_ptr<Menu> menu = nullptr;

    rl::tmx_map *tmx_data = nullptr;
    std::shared_ptr<rg::Frames> water_frames = nullptr;

    bool raining{};
    bool shop_active{};

    // music
    rg::mixer::Sound success = rg::mixer::Sound("resources/audio/success.wav");
    rg::mixer::Sound music = rg::mixer::Sound("resources/audio/music.mp3", true);

    std::shared_ptr<rg::Surface> ground_surf = nullptr;
};
