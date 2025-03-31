#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main()
{
    // VARIABLES FOR TITLE SCREEN
    //--------------------------------------------------------------------------------------

    // Defining screen size - exactly half of 1080p here!
    int screenWidth = 960;
    int screenHeight = 540;

    // Colors: Red green blue yellow orange pink grey white
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {  
        
        //------------------------------- DRAWING PART ----------------------------------//
        BeginDrawing();
        EndDrawing();

    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
