#include "include/raylib.h"
#include "include/raymath.h"
#include <math.h>

#define SCREENHEIGHT 1080
#define SCREENWIDTH  1920
#define GRIDSIZE 20
#define TILESIZE 64

// Green color palatte from lighest to darkest
#define C1 (Color){ 138, 189, 76 }
#define C2 (Color){ 64, 133, 109 }
#define C3 (Color){ 48, 102, 87 }
#define C4 (Color){ 36, 76, 64 }

float tile_height[GRIDSIZE][GRIDSIZE] = { 0 };

Vector2 IsoTransform(Vector2 coordinate) {
    float x = 0.5 * coordinate.x - 0.5 * coordinate.y;
    float y = 0.25 * coordinate.x + 0.25 * coordinate.y;
    x -= TILESIZE / 2;
    x += SCREENWIDTH / 2;
    y += SCREENHEIGHT / 4;
    return (Vector2){ x, y };
}

void DrawTiles() {
    Texture2D basic_tile = LoadTexture("assets/basic_tile.png");
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++) {
            Vector2 origin = { TILESIZE * j, TILESIZE * i };
            origin = IsoTransform(origin);
            // Raise blocks according to their height
            origin.y -= tile_height[j][i] * TILESIZE * 0.5;
            DrawTextureV(basic_tile, origin, WHITE);
        }
}

int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic ball program");
    SetTargetFPS(60);

    while (WindowShouldClose() != true) {
        for (int i = 0; i < GRIDSIZE; i++)
            for (int j = 0; j < GRIDSIZE; j++)
                tile_height[j][i] = 0.25 * sin(3 * GetTime() + (j + i));

        BeginDrawing();
        ClearBackground(C1);
        DrawTiles();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
