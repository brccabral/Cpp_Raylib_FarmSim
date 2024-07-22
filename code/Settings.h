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

inline InsertOrderMap<std::string, unsigned int> LAYERS = {
        {"water", 0}, //
        {"ground", 1}, //
        {"soil", 2}, //
        {"soil water", 3}, //
        {"rain floor", 4}, //
        {"house floor", 5}, //
        {"house bottom", 6}, //
        {"ground plant", 7}, //
        {"house walls", 8}, //
        {"main", 9}, //
        {"house top", 10}, //
        {"fruit", 11}, //
        {"rain drops", 12}, //
};
