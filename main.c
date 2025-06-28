#include "include/raylib.h"
#include "include/raymath.h"

#define SCREENHEIGHT 1080
#define SCREENWIDTH  1920

int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic ball program");
    SetTargetFPS(60);

    Texture2D basic_tile = LoadTexture("assets/basic_tile.png");

    int x = 10;

    while (WindowShouldClose() != true)
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (IsKeyDown(KEY_RIGHT))
            x++;

        DrawTexture(basic_tile, x, 10, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
