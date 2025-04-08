#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

float alphaMain = 0.0f;

int main(void)
{
    bool mainScreen = false;
    bool gamemodeScreen = false;
    
    bool startingScreen = false;
    
    bool normalScreen = true;
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
    
    // -- NORMAL -- //
    
    float NormalBtnX = 550;
    float NormalBtnY = 450;
    char NormalText[7] = "NORMAL";
    Vector2 posNormalText = {330, 390};
    int NormalTextSize = 120;
    Vector2 posNormalShdw = {337, 397};
    
    float invisNormalBtnX = 290;
    float invisNormalBtnY = 350;
    Rectangle invisNormalBtn = {invisNormalBtnX, invisNormalBtnY, 550, 200};
    
    // -- ADVANCED -- //
    
    float AdvancedBtnX = 1300;
    float AdvancedBtnY = 450;
    char AdvancedText[9] = "ADVANCED";
    Vector2 posAdvancedText = {1035, 395};
    int AdvancedTextSize = 110;
    Vector2 posAdvancedShdw = {1042, 402};
    
    float invisAdvancedBtnX = 1020;
    float invisAdvancedBtnY = 350;
    Rectangle invisAdvancedBtn = {invisAdvancedBtnX, invisAdvancedBtnY, 550, 200};
    
    // -- ZEN -- //
    
    float ZenBtnX = 550;
    float ZenBtnY = 850;
    char ZenText[4] = "ZEN";
    Vector2 posZenText = {425, 780};
    int ZenTextSize = 150;
    Vector2 posZenShdw = {432, 787};
    
    float invisZenBtnX = 290;
    float invisZenBtnY = 750;
    Rectangle invisZenBtn = {invisZenBtnX, invisZenBtnY, 550, 200};
    
    // -- ENDLESS -- //
    
    float EndlessBtnX = 1300;
    float EndlessBtnY = 850;
    char EndlessText[8] = "ENDLESS";
    Vector2 posEndlessText = {1080, 795};
    int EndlessTextSize = 120;
    Vector2 posEndlessShdw = {1087, 802};
    
    float invisEndlessBtnX = 1020;
    float invisEndlessBtnY = 750;
    Rectangle invisEndlessBtn = {invisEndlessBtnX, invisEndlessBtnY, 550, 200};
    
    // -- GAMEMODE ALPHA -- //
    
    float alphaGamemode = 0.0f;
    float alphaGamemodeBtns = 0.0f;
    
    // ---------------------- STARTING SCREEN --------------------- //
    
    float alphaNUM3 = 0.0f;
    float alphaNUM2 = 0.0f;
    float alphaNUM1 = 0.0f;
    float alphaGO = 0.0f;
    
    char StartingTHREE[2] = "3";
    char StartingTWO[2] = "2";
    char StartingONE[2] = "1";
    char StartingGO[3] = "GO";

    // ---------------------- NORMAL MODE GAME -------------------- //
    
    float DropShadowX = 150;
    float DropShadowY = 0;
    Rectangle DropShadow = {DropShadowX, DropShadowY, 900, 1100};
    float alphaDropShadow = 0.5f;
    
    float FocusBarX = 150;
    float FocusBarY = 900;
    Rectangle FocusBar = {FocusBarX, FocusBarY, 900, 200};
    
    float SelectBarX = 1250;
    float SelectBarY = 0;
    Rectangle SelectBar = {SelectBarX, SelectBarY, 600, 1100};
    
    float SelectBarTextX = 1275;
    float SelectBarTextY = 50;
    float SelectBarTextSize = 100;
    Vector2 posSelectBarText = {SelectBarTextX, SelectBarTextY};
    
    // CIRCLES ON FOCUS BAR
    
    float CIRCLE1x = 290;
    float CIRCLE1y = 990;
    
    float CIRCLE2x = 490;
    float CIRCLE2y = 990;
    
    float CIRCLE3x = 695;
    float CIRCLE3y = 990;
    
    float CIRCLE4x = 900;
    float CIRCLE4y = 990;
    
    // CIRCLES ON SELECT BAR - RED, GREEN, BLUE, YELLOW, ORANGE, PINK, GREY, WHITE
    
    float CIRCLEredX = 1425;
    float CIRCLEredY = 275;
    
    float CIRCLEgreenX = 1675;
    float CIRCLEgreenY = 275;  
    
    float CIRCLEblueX = 1350;
    float CIRCLEblueY = 400;  
    
    float CIRCLEyellowX = 1350;
    float CIRCLEyellowY = 400;   
    
    float CIRCLEorangeX = 1350;
    float CIRCLEorangeY = 400;    
    
    float CIRCLEpinkX = 1350;
    float CIRCLEpinkY = 400;  
    
    float CIRCLEgreyX = 1350;
    float CIRCLEgreyY = 400;   
    
    float CIRCLEwhiteX = 1350;
    float CIRCLEwhiteY = 400;
    
    float CIRCLEdeleteX = 1450;
    float CIRCLEdeleteY = 890;
    
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
        
        if (isHoveringNormalBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            startingScreen = true;
            printf("endless.");
            fflush(stdout);   
        } else if (isHoveringNormalBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        
        if (isHoveringAdvancedBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            startingScreen = true;
            printf("advanced.");
            fflush(stdout);   
        } else if (isHoveringAdvancedBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        
        if (isHoveringZenBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            startingScreen = true;
            printf("zen.");
            fflush(stdout);   
        } else if (isHoveringZenBtn && mainScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        
        if (isHoveringEndlessBtn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == true) {
            gamemodeScreen = false;
            startingScreen = true;
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
                
                DrawRectangleRec(invisNormalBtn, Fade(RED, alphaGamemodeBtns));
                DrawRectangleRec(invisAdvancedBtn, Fade(RED, alphaGamemodeBtns));
                DrawRectangleRec(invisZenBtn, Fade(RED, alphaGamemodeBtns));
                DrawRectangleRec(invisEndlessBtn, Fade(RED, alphaGamemodeBtns));
            }
            
            if (startingScreen) {
                if (alphaNUM3 < 1) {
                    if (alphaNUM3 < 1) alphaNUM3 += 0.02f;
                    DrawText(StartingTHREE, 700, 100, 1000, Fade(GOLD, alphaNUM3));
                } else if (alphaNUM2 < 1) {
                    if (alphaNUM3 == 1) alphaNUM3 -= 0.9f;
                    if (alphaNUM2 < 1) alphaNUM2 += 0.02f;
                    DrawText(StartingTWO, 700, 100, 1000, Fade(GOLD, alphaNUM2));
                } else if (alphaNUM1 < 1) {
                    if (alphaNUM2 == 1) alphaNUM2 -= 0.9f;
                    if (alphaNUM1 < 1) alphaNUM1 += 0.02f;
                    DrawText(StartingONE, 800, 100, 1000, Fade(GOLD, alphaNUM1));
                } else if (alphaGO < 1) {
                    if (alphaNUM1 == 1) alphaNUM1 -= 0.9f;
                    if (alphaGO < 1) alphaGO += 0.01f;
                    DrawText(StartingGO, 300, 100, 1000, Fade(GOLD, alphaGO));
                } else {
                    normalScreen = true;
                }
                
            }
            
            if (normalScreen) {
                
                DrawRectangleRec(DropShadow, Fade(DARKGRAY, alphaDropShadow));
                
                // FOCUS BAR
                DrawRectangleRec(FocusBar, GRAY);        
                DrawEllipse(CIRCLE1x, CIRCLE1y, 85, 85, Fade(DARKGRAY, alphaDropShadow));
                DrawEllipseLines(CIRCLE1x, CIRCLE1y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE1x, CIRCLE1y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE1x, CIRCLE1y, 87, 87, BLACK);
                
                DrawEllipse(CIRCLE2x, CIRCLE2y, 85, 85, Fade(DARKGRAY, alphaDropShadow));
                DrawEllipseLines(CIRCLE2x, CIRCLE2y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE2x, CIRCLE2y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE2x, CIRCLE2y, 87, 87, BLACK);
                
                DrawEllipse(CIRCLE3x, CIRCLE3y, 85, 85, Fade(DARKGRAY, alphaDropShadow));
                DrawEllipseLines(CIRCLE3x, CIRCLE3y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE3x, CIRCLE3y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE3x, CIRCLE3y, 87, 87, BLACK);
                
                DrawEllipse(CIRCLE4x, CIRCLE4y, 85, 85, Fade(DARKGRAY, alphaDropShadow));
                DrawEllipseLines(CIRCLE4x, CIRCLE4y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE4x, CIRCLE4y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE4x, CIRCLE4y, 87, 87, BLACK);
                
                // SELECT BAR
                DrawRectangleRec(SelectBar, DARKGRAY);
                DrawTextEx(font, Title, posSelectBarText, SelectBarTextSize, 8, WHITE);
                
                DrawEllipse(CIRCLEredX, CIRCLEredY, 85, 85, RED);
                DrawEllipseLines(CIRCLEredX, CIRCLEredY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEredX, CIRCLEredY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEredX, CIRCLEredY, 87, 87, BLACK);

                DrawEllipse(CIRCLEgreenX, CIRCLEgreenY, 85, 85, GREEN);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 87, 87, BLACK);
                
                // KEEP DOING COLORS
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