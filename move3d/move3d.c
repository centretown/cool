/*******************************************************************************************
 *
 *   project_name
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
#include "raylib.h"
#include "../lib/gpads.h"
#include "../lib/kbd.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = {0};
Vector3 cubePosition = {0};
Cmd command = CMD_UNDEFINED;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void); // Update and draw one frame
static Cmd UpdateInput(void);      // Update input state

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Set MSAA 4X hint before windows creation
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTraceLogLevel(LOG_NONE);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib - project_name");

    camera.position = (Vector3){3.0f, 3.0f, 2.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    Cmd cmd = UpdateInput();
    switch (cmd)
    {
    case CMD_NONE:
        break;
    case CMD_MOVE_LEFT:
        cubePosition.x -= .1;
        break;
    case CMD_MOVE_RIGHT:
        cubePosition.x += .1;
        break;
    case CMD_MOVE_UP:
        cubePosition.z -= .1;
        break;
    case CMD_MOVE_DOWN:
        cubePosition.z += .1;
        break;
    case CMD_MOVE_IN:
        cubePosition.y += .1;
        break;
    case CMD_MOVE_OUT:
        cubePosition.y -= .1;
        break;
    case CMD_MOVE_HOME:
        cubePosition.x = 0;
        cubePosition.y = 0;
        cubePosition.z = 0;
        break;

    default:
        break;
    }

    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera, CAMERA_ORBITAL);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
    DrawGrid(10, 1.0f);

    EndMode3D();

    DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

static Cmd UpdateInput(void)
{
    Cmd cmd = CheckGamePads();
    if (cmd == CMD_UNDEFINED)
    {
        cmd = checkKeyboard();
    }
    return cmd;
}
