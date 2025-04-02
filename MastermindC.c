#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

float alphaMain = 0.0f;

int main(void)
{
    bool mainScreen = true;
    bool gamemodeScreen = false;
    
    bool normalScreen = false;
    bool advancedScreen = false;
    bool zenScreen = false;
    bool endlessScreen = false;
    
    // ----------------------- TITLE SCREEN ----------------------- //
    
    char Title[11] = "Mastermind";
    Vector2 posTitle = {290, 100};
    int TitleSize = 250;
    
    float PlayBtnX = 930;
    float PlayBtnY = 650;

    char PlayText[5] = "PLAY";
    Vector2 posPlayText = {760, 580};
    int PlayTextSize = 150;
    
    Vector2 posPlayShdw = {767, 587};
    
    float PlayInvisX = 700;
    float PlayInvisY = 560;
    Rectangle invisPlayBtn = {PlayInvisX, PlayInvisY, 470, 180};
    float alphaInvis = 0.0f;
    // ---------------------- GAMEMODE CHOICE --------------------- //
    
    char gamemodeTitle[22] = "CHOOSE YOUR GAMEMODE";
    Vector2 posGamemodeTitle = {75, 100};
    int gamemodeTitleSize = 150;
    
    float NormalBtnX = 550;
    float NormalBtnY = 450;
    char NormalText[7] = "NORMAL";
    Vector2 posNormalText = {330, 390};
    int NormalTextSize = 120;
    Vector2 posNormalShdw = {337, 397};
    
    float AdvancedBtnX = 1300;
    float AdvancedBtnY = 450;
    char AdvancedText[9] = "ADVANCED";
    Vector2 posAdvancedText = {1035, 395};
    int AdvancedTextSize = 110;
    Vector2 posAdvancedShdw = {1042, 402};
    
    float ZenBtnX = 550;
    float ZenBtnY = 850;
    char ZenText[4] = "ZEN";
    Vector2 posZenText = {425, 780};
    int ZenTextSize = 150;
    Vector2 posZenShdw = {432, 787};
    
    float EndlessBtnX = 1300;
    float EndlessBtnY = 850;
    char EndlessText[8] = "ENDLESS";
    Vector2 posEndlessText = {1080, 795};
    int EndlessTextSize = 120;
    Vector2 posEndlessShdw = {1087, 802};
    
    
    
    
    float alphaGamemode = 0.0f;
    
    
    // ---------------------- INITIALIZATION ---------------------- //
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    ToggleBorderlessWindowed();
    
    InitWindow(screenWidth, screenHeight, "Mastermind");
    SetTargetFPS(60);
    
    
    //--------------------------------------------------------------------------------------

    Font font = LoadFont("pixantiqua.png");
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Vector2 MousePos = GetMousePosition();
        bool isHoveringPlayBtn = CheckCollisionPointRec(MousePos, invisPlayBtn);
        
        bool isHoveringNormalBtn = CheckCollisionPointRec(MousePos, invisNormalBtn);
        bool isHoveringAdvancedBtn = CheckCollisionPointRec(MousePos, invisAdvancedBtn);
        bool isHoveringZenBtn = CheckCollisionPointRec(MousePos, invisZenBtn);
        bool isHoveringEndlessBtn = CheckCollisionPointRec(MousePos, invisEndlessBtn);
        
        if (isHoveringPlayBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mainScreen == true) {
            mainScreen = false;
            gamemodeScreen = true;
            printf("DEBUG!!!!!!!!!!!!!!!!!!!!!!!");
            fflush(stdout);
        } else if (isHoveringPlayBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        
        
        if (isHoveringAdvancedBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            advancedScreen = true;
            printf("advanced.");
            fflush(stdout);   
        } else if (isHoveringAdvancedBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        
        if (isHoveringZenBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            zenScreen = true;
            printf("zen.");
            fflush(stdout);   
        } else if (isHoveringZenBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        
        if (isHoveringEndlessBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            endlessScreen = true;
            printf("endless.");
            fflush(stdout);   
        } else if (isHoveringEndlessBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            if (mainScreen) {
                if (alphaMain < 1) alphaMain += 0.01f;
                DrawTextEx(font, Title, posTitle, TitleSize, 15, Fade(GOLD, alphaMain)); // OBS! Order of operators: (Font var, string var, position var, SIZE, KERNING, COLOR);
                DrawEllipse(PlayBtnX, PlayBtnY, 250, 100, Fade(GOLD, alphaMain));
                DrawRectangleRec(invisPlayBtn, Fade(WHITE, alphaInvis));
                DrawTextEx(font, PlayText, posPlayShdw, PlayTextSize, 8, Fade(BLACK, alphaMain));
                DrawTextEx(font, PlayText, posPlayText, PlayTextSize, 8, Fade(WHITE, alphaMain));
            }
            
            if (gamemodeScreen) {
                if (alphaGamemode < 1) alphaGamemode += 0.05f;
                DrawTextEx(font, gamemodeTitle, posGamemodeTitle, gamemodeTitleSize, 12, Fade(GOLD, alphaGamemode));
                
                DrawEllipse(NormalBtnX, NormalBtnY, 300, 100, Fade(GOLD, alphaGamemode));
                DrawEllipse(AdvancedBtnX, AdvancedBtnY, 300, 100, Fade(GOLD, alphaGamemode));
                DrawEllipse(ZenBtnX, ZenBtnY, 300, 100, Fade(GOLD, alphaGamemode));
                DrawEllipse(EndlessBtnX, EndlessBtnY, 300, 100, Fade(GOLD, alphaGamemode));

                                
                DrawTextEx(font, NormalText, posNormalShdw, NormalTextSize, 8, Fade(BLACK, alphaGamemode));
                DrawTextEx(font, NormalText, posNormalText, NormalTextSize, 8, Fade(WHITE, alphaGamemode));
                
                DrawTextEx(font, AdvancedText, posAdvancedShdw, AdvancedTextSize, 8, Fade(BLACK, alphaGamemode));
                DrawTextEx(font, AdvancedText, posAdvancedText, AdvancedTextSize, 8, Fade(WHITE, alphaGamemode));
                
                DrawTextEx(font, ZenText, posZenShdw, ZenTextSize, 8, Fade(BLACK, alphaGamemode));
                DrawTextEx(font, ZenText, posZenText, ZenTextSize, 8, Fade(WHITE, alphaGamemode));
                
                DrawTextEx(font, EndlessText, posEndlessShdw, EndlessTextSize, 8, Fade(BLACK, alphaGamemode));
                DrawTextEx(font, EndlessText, posEndlessText, EndlessTextSize, 8, Fade(WHITE, alphaGamemode));
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}