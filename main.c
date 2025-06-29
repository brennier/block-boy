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

typedef enum PlayerState {
    WALKING_RIGHT,
    WALKING_LEFT,
    WALKING_UP,
    WALKING_DOWN,
    STANDING
} PlayerState;

typedef struct Player {
    PlayerState state;
    int x;
    int y;
} Player;

float tile_height[GRIDSIZE][GRIDSIZE] = { 0 };

Vector2 IsoTransform(Vector2 coordinate) {
    float x = 0.5 * coordinate.x - 0.5 * coordinate.y;
    float y = 0.25 * coordinate.x + 0.25 * coordinate.y;
    x -= TILESIZE / 2;
    x += SCREENWIDTH / 2;
    y += SCREENHEIGHT / 4;
    return (Vector2){ x, y };
}

void DrawPlayer(Player player, Texture2D player_sprite) {
    Vector2 pos = (Vector2){ player.x, player.y };
    pos = Vector2Scale(pos, TILESIZE);
    pos = IsoTransform(pos);
    // Raise the player up so his feet are on grid
    pos.y -= TILESIZE / 2;
    pos.y -= TILESIZE / 8;
    // Raise his up to the tile's height
    pos.y -= tile_height[player.x][player.y] * TILESIZE * 0.5;
    DrawTextureV(player_sprite, pos, WHITE);
}

void DrawTiles(Texture2D basic_tile) {
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
    Texture2D border = LoadTexture("assets/gameboy_border.png");
    Texture2D basic_tile = LoadTexture("assets/basic_tile.png");
    Texture2D player_sprite = LoadTexture("assets/player.png");
    Player player = {
        .state = STANDING,
        .x = GRIDSIZE / 2,
        .y = GRIDSIZE / 2
    };
    tile_height[5][5] = 1;
    tile_height[5][8] = 2;
    SetTargetFPS(60);

    while (WindowShouldClose() != true) {
        if (IsKeyDown(KEY_RIGHT))
            player.x += 1;
        if (IsKeyDown(KEY_LEFT))
            player.x -= 1;
        if (IsKeyDown(KEY_DOWN))
            player.y += 1;
        if (IsKeyDown(KEY_UP))
            player.y -= 1;

        BeginDrawing();
        ClearBackground(C1);
        DrawTiles(basic_tile);
        DrawPlayer(player, player_sprite);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
