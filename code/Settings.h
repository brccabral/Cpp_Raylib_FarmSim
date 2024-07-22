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

inline InsertOrderMap LAYERS = {"water",       "ground",       "soil",         "soil water",  "rain floor",
                                "house floor", "house bottom", "ground plant", "house walls", "main",
                                "house top",   "fruit",        "rain drops"};
