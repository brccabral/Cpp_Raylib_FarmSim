#pragma once
#include <raylib.h>


class Game
{
public:

    Game(int width, int height);
    ~Game();
    void Draw();
    void run();

    RenderTexture2D display_surface;

private:

    void UnloadResources();
    void DisplayUpdate() const;
};
