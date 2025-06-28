#include "include/raylib.h"
#include "include/raymath.h"

#define SCREENHEIGHT 1080
#define SCREENWIDTH  1920
#define GRIDSIZE 10
#define TILESIZE 64

void DrawTiles() {
    Texture2D basic_tile = LoadTexture("assets/basic_tile.png");
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
            DrawTexture(basic_tile, TILESIZE * j, TILESIZE * i, WHITE);
}

int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic ball program");
    SetTargetFPS(60);


    int x = 10;

    while (WindowShouldClose() != true)
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (IsKeyDown(KEY_RIGHT))
            x++;

        DrawTiles();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
