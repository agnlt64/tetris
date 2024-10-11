
#include <string>

#include "include/raylib/raylib.h"
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("assets/fonts/monogram.ttf", 64, 0, 0);

    Game game = Game();

    double timeStarted = 1.0f;
    float interval = 0.5f;

    while (WindowShouldClose() == false)
    {
        timeStarted += GetFrameTime();

        if ((int)timeStarted % 90 == 0)
        {
            interval = std::max(0.15f, interval - 0.05f);
            timeStarted = 1.0f;
        }

        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(interval))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
            timeStarted = 1.0f;
            interval = 0.5f;
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        std::string scoreText = std::to_string(game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText.c_str(), 38, 2);

        DrawTextEx(font, scoreText.c_str(), {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}