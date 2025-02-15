#include <raylib.h>
#include "game.hpp"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 700

std::string FormatWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{
    int offset = 50;
    Color background_grey = {30, 30, 30, 255};
    Color yellow = {243, 216, 63, 255};
    InitWindow(SCREEN_WIDTH + offset, SCREEN_HEIGHT + 2 * offset, "Space Invaders");
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    InitAudioDevice();
    Game game;

    Texture2D spaceshipImage = LoadTexture("resources/spaceship.png");
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.getMusic());
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(background_grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 100, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if (game.GetRun())
        {
            std::string hell = "HELL ";
            std::string level = hell.append(FormatWithLeadingZeros(game.GetLevel(), 3));
            DrawTextEx(font, level.c_str(), {570, 740}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER!", {570, 740}, 34, 2, yellow);
        }
        float x = 50.0;
        for (int i = 0; i < game.GetLives(); i++)
        {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.GetScore(), 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        game.Draw();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}