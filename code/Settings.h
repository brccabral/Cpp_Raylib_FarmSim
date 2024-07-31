#pragma once
#include <map>
#include <string>
#include <rygame.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int TILE_SIZE = 64;

inline std::map<std::string, rl::Vector2> OVERLAY_POSITIONS = {
        {"tool", {40, SCREEN_HEIGHT - 15}}, //
        {"seed", {70, SCREEN_HEIGHT - 5}}, //
};

inline rg::InsertOrderMap<std::string, unsigned int> LAYERS = {
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

inline rg::InsertOrderMap<std::string, std::vector<rl::Vector2>> APPLE_POS = {
        {"Small", {{18, 17}, {30, 37}, {12, 50}, {30, 45}, {20, 30}, {30, 10}}},
        {"Large", {{30, 24}, {60, 65}, {50, 50}, {16, 40}, {45, 50}, {42, 70}}},
};

inline std::map<std::string, rl::Vector2> PLAYER_TOOL_OFFSET = {
        {"left", {-50, 40}}, //
        {"right", {50, 40}}, //
        {"up", {0, -10}}, //
        {"down", {0, 50}}, //
};

inline std::map<std::string, float> GROW_SPEED = {
        {"corn", 1.0f}, //
        {"tomato", 0.7f}, //
};

inline std::map<std::string, unsigned int> SALE_PRICES = {
        {"wood", 4}, //
        {"apple", 2}, //
        {"corn", 10}, //
        {"tomato", 20}, //
};

inline std::map<std::string, unsigned int> PURCHASE_PRICES = {
        {"corn", 4}, //
        {"tomato", 5}, //
};
