#pragma once
#include <map>
#include <string>
#include <raylib.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

inline std::map<std::string, Vector2> OVERLAY_POSITIONS = {
        {"tool", {40, SCREEN_HEIGHT - 15}}, //
        {"seed", {70, SCREEN_HEIGHT - 5}}, //
};

inline std::vector<std::string> LAYERS_ORDER = {"water",      "ground",       "soil",         "soil water",
                                                "rain floor", "house bottom", "ground plant", "main",
                                                "house top",  "fruit",        "rain drops"};

inline std::map<std::string, unsigned int> LAYERS = {
        {"water", 0}, //
        {"ground", 1}, //
        {"soil", 2}, //
        {"soil water", 3}, //
        {"rain floor", 4}, //
        {"house bottom", 5}, //
        {"ground plant", 6}, //
        {"main", 7}, //
        {"house top", 8}, //
        {"fruit", 9}, //
        {"rain drops", 10}, //
};
