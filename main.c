#include "include/raylib.h"
#include "include/raymath.h"

#define SCREENHEIGHT 480
#define SCREENWIDTH  720

int main() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic ball program");
    SetTargetFPS(60);

    while (WindowShouldClose() != true)
    {
        BeginDrawing();

        DrawRectangle(10, 10, 100, 100, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
