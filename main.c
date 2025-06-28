#include "include/raylib.h"
#include "include/raymath.h"
#include <math.h>
#define SCREENHEIGHT 930
#define SCREENWIDTH  1120
#define GRIDSIZE 20
#define TILESIZE 64

// Green color palatte from lighest to darkest
#define C1 (Color){ 138, 189, 76 }
#define C2 (Color){ 64, 133, 109 }
#define C3 (Color){ 48, 102, 87 }
#define C4 (Color){ 36, 76, 64 }

float tile_height[GRIDSIZE][GRIDSIZE] = { 0 };
Vector2 tile_offset = { 0 };

Vector2 IsoTransform(Vector2 coordinate) {
    float x = 0.5 * coordinate.x - 0.5 * coordinate.y;
    float y = 0.25 * coordinate.x + 0.25 * coordinate.y;
    x -= TILESIZE / 2;
    x += SCREENWIDTH / 2;
    y += SCREENHEIGHT / 4;
    return (Vector2){ x, y };
}

void DrawTiles(Texture2D basic_tile) {
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++) {
            Vector2 origin = { TILESIZE * j, TILESIZE * i };
            origin = IsoTransform(origin);
            // Raise blocks according to their height
            origin.y -= tile_height[j][i] * TILESIZE * 0.5;
            DrawTextureV(basic_tile, Vector2Add(origin, tile_offset), WHITE);
        }
}

int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic ball program");
    Texture2D border = LoadTexture("assets/gameboy_border.png");
    Texture2D basic_tile = LoadTexture("assets/basic_tile.png");
    SetTargetFPS(60);

    while (WindowShouldClose() != true) {
        for (int i = 0; i < GRIDSIZE; i++)
            for (int j = 0; j < GRIDSIZE; j++) {
                tile_height[j][i] =  sin(M_PI * GetTime());
                tile_height[j][i] += sin(M_PI * GetTime() + i);
                tile_height[j][i] += sin(M_PI * GetTime() + j);
                tile_height[j][i] *= 0.25;
            }

        if (IsKeyDown(KEY_RIGHT))
            tile_offset.x -= 3;
        if (IsKeyDown(KEY_LEFT))
            tile_offset.x += 3;
        if (IsKeyDown(KEY_DOWN))
            tile_offset.y -= 3;
        if (IsKeyDown(KEY_UP))
            tile_offset.y += 3;



        BeginDrawing();
        ClearBackground(C1);
        DrawTiles(basic_tile);
        DrawTexture(border, 0, 0, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
