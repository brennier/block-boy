#include "include/raylib.h"
#include "include/raymath.h"
#include <math.h>
#define SCREENHEIGHT 1080
#define SCREENWIDTH  1920
#define GRIDSIZE 20
#define TILESIZE 64
#define INPUT_DELAY .2 // delay in seconds

// Green color palatte from lighest to darkest
#define C1 (Color){ 138, 189, 76 }
#define C2 (Color){ 64, 133, 109 }
#define C3 (Color){ 48, 102, 87 }
#define C4 (Color){ 36, 76, 64 }

Texture2D player_sprite;
Texture2D basic_tile;

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

void DrawPlayer(Player player) {
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

void DrawTile(int row, int col) {
    Vector2 origin = { TILESIZE * row, TILESIZE * col };
    origin = IsoTransform(origin);
    // Draw a column of blocks according to the height
    for (int height = 0; height <= tile_height[row][col]; height++) {
        float y = origin.y - height * TILESIZE * 0.5;
        DrawTexture(basic_tile, origin.x, y, WHITE);
    }
}

void DrawGame(Player player) {
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++) {
            DrawTile(j, i);
            if (j == player.x && i == player.y)
                DrawPlayer(player);
        }
}

int main() {
    // Use VSync to refresh along with the monitor
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic ball program");
    Texture2D border = LoadTexture("assets/gameboy_border.png");
    basic_tile = LoadTexture("assets/basic_tile.png");
    player_sprite = LoadTexture("assets/player.png");
    Player player = {
        .state = STANDING,
        .x = GRIDSIZE / 2,
        .y = GRIDSIZE / 2
    };
    tile_height[5][5] = 1;
    tile_height[5][8] = 2;
    float input_delay = 0;
    float delta_time = 0.0;

    while (WindowShouldClose() != true) {
        float delta_time = GetFrameTime();
        if (player.state == STANDING) {
            if (IsKeyDown(KEY_RIGHT)) {
                player.x += 1;
                player.state = WALKING_RIGHT;
                input_delay = INPUT_DELAY;
            }
            if (IsKeyDown(KEY_LEFT)) {
                player.x -= 1;
                player.state = WALKING_LEFT;
                input_delay = INPUT_DELAY;
            }
            if (IsKeyDown(KEY_DOWN)) {
                player.y += 1;
                player.state = WALKING_DOWN;
                input_delay = INPUT_DELAY;
            }
            if (IsKeyDown(KEY_UP)) {
                player.y -= 1;
                player.state = WALKING_UP;
                input_delay = INPUT_DELAY;
            }
        }

        if (input_delay < 0)
            input_delay = 0;
        else if (input_delay > 0)
            input_delay -= delta_time;
        else
            player.state = STANDING;

        BeginDrawing();
        ClearBackground(C1);
        DrawGame(player);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
