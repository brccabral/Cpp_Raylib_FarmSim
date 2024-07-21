#pragma once

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

inline std::map<std::string, Vector2> OVERLAY_POSITIONS = {
        {"tool", {40, SCREEN_HEIGHT - 15}},
        {"seed", {70, SCREEN_HEIGHT - 5}},
};
