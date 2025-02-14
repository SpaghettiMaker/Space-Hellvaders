#include <raylib.h>
#include "game.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 700

int main()
{
    Color background_grey = {30, 30, 30, 255};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();
        BeginDrawing();
        ClearBackground(background_grey);
        game.Draw();
        game.Update();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}