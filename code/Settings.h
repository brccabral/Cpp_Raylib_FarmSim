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

inline InsertOrderMap<std::string, std::vector<Vector2>> APPLE_POS = {
        {"Small", {{18, 17}, {30, 37}, {12, 50}, {30, 45}, {20, 30}, {30, 10}}},
        {"Large", {{30, 24}, {60, 65}, {50, 50}, {16, 40}, {45, 50}, {42, 70}}},
};

inline std::map<std::string, Vector2> PLAYER_TOOL_OFFSET = {
        {"left", {-50, 40}}, //
        {"right", {50, 40}}, //
        {"up", {0, -10}}, //
        {"down", {0, 50}}, //
};
