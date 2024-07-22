#include <raylib.h>
#include <raylib-tmx.h>
#include <raylib_utils.h>

int main()
{
    InitWindow(1200, 800, "test");
    // InitWindow(50 * 64, 40 * 64, "test");
    SetTargetFPS(60);

    auto *surface = new Surface(50 * 64, 40 * 64);
    Image image = GenImageColor(64, 64, WHITE);
    Texture texture = LoadTextureFromImage(image);
    surface->Blit(&texture);


    const auto *tmx_data = LoadTMX("resources/data/map.tmx");

    // house
    const tmx_layer *house_bottom = tmx_find_layer_by_name(tmx_data, "HouseFurnitureBottom");

    auto *house_bottom_surf = GetTMXLayerSurface(tmx_data, house_bottom);

    surface->Blit(house_bottom_surf->Texture());

    float posX = 0;
    float posY = 0;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_DOWN))
        {
            posY += 400 * GetFrameTime();
        }
        if (IsKeyDown(KEY_UP))
        {
            posY -= 400 * GetFrameTime();
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            posX += 400 * GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT))
        {
            posX -= 400 * GetFrameTime();
        }


        BeginDrawing();
        ClearBackground(RED);

        // DrawTextureRec(*surface->Texture(), surface->atlas_rect.rectangle, {0, 0}, WHITE);
        // DrawTexture(*house_bottom_surf->Texture(), posX, posY, WHITE);
        DrawTexture(*surface->Texture(), posX, posY, WHITE);
        // DrawTexture(texture, posX, posY, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadImage(image);

    CloseWindow();
    return 0;
}
