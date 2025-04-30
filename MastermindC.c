#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

float alphaMain = 0.0f;

char storedMemoryBarArray[9][5];
int memBarCount = 0;

int RNGcount = 0;
char RNGnums[5] = "";

void addCharRNG(char c) {
    int len = strlen(RNGnums);

    if (len < 4) {  // Ensure there's space for the new char (4 chars + 1 for \0)
        RNGnums[len] = c;  // add the new char
        RNGnums[len + 1] = '\0';  // null terminate the string
    } else {
        printf("No space left to add another character.\n");
    }
}

void addChar(char c) {
    int len = strlen(storedMemoryBarArray[memBarCount]);

    if (len < 4) {  // Ensure there's space for the new char (4 chars + 1 for \0)
        storedMemoryBarArray[memBarCount][len] = c;  // add the new char
        storedMemoryBarArray[memBarCount][4] = '\0';
        RNGnums[4] = '\0';
    } else {
        printf("No space left to add another character.\n");
    }
}

void deleteChar() {
    int len = strlen(storedMemoryBarArray[memBarCount]);

    if (len == 0) {
        printf("Nothing to delete.\n");
        return;
    }

    storedMemoryBarArray[memBarCount][len - 1] = '\0';  // overwrite last char with null terminator
}

void RNG(int minNum, int maxNum) {
    
    memset(RNGnums, 0, sizeof(RNGnums));
    
    for (int i = 0; i < 4; i++) {
        int value = (rand() % maxNum) + minNum;
        char valueStr[2];
        sprintf(valueStr, "%d", value);
        addCharRNG(valueStr[0]);
    }
    printf("THE COMBINATION IS: %s\n\n", RNGnums);
}

const char* ColorName(Color c) {
    if (memcmp(&c, &RED, sizeof(Color)) == 0) return "RED";
    if (memcmp(&c, &GREEN, sizeof(Color)) == 0) return "GREEN";
    if (memcmp(&c, &BLUE, sizeof(Color)) == 0) return "BLUE";
    if (memcmp(&c, &YELLOW, sizeof(Color)) == 0) return "YELLOW";
    if (memcmp(&c, &ORANGE, sizeof(Color)) == 0) return "ORANGE";
    if (memcmp(&c, &PINK, sizeof(Color)) == 0) return "PINK";
    if (memcmp(&c, &GRAY, sizeof(Color)) == 0) return "GRAY";
    if (memcmp(&c, &WHITE, sizeof(Color)) == 0) return "WHITE";
    return "UNKNOWN";
}

int main(void)
{
    RNGnums[0] = '\0';
    
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
    
    float alphaVis = 1.0f;
    
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
    
    float SubmitBtnX = 1150;
    float SubmitBtnY = 990;
    float alphaSubmit = 1.0f;
    Rectangle invisSumbitBtn = {SubmitBtnX-50, SubmitBtnY-50, 100, 100};
    
    
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
    float alphaRED = 1.0f;
    Rectangle invisCIRCLEred = {CIRCLEredX-80, CIRCLEredY-80, 160, 160};
    
    float CIRCLEgreenX = 1675;
    float CIRCLEgreenY = 275;
    float alphaGREEN = 1.0f;
    Rectangle invisCIRCLEgreen = {CIRCLEgreenX-80, CIRCLEgreenY-80, 160, 160};
    
    float CIRCLEblueX = 1425;
    float CIRCLEblueY = 475;  
    float alphaBLUE = 1.0f;
    Rectangle invisCIRCLEblue = {CIRCLEblueX-80, CIRCLEblueY-80, 160, 160};
   
    float CIRCLEyellowX = 1675;
    float CIRCLEyellowY = 475;
    float alphaYELLOW = 1.0f;
    Rectangle invisCIRCLEyellow = {CIRCLEyellowX-80, CIRCLEyellowY-80, 160, 160};    
    
    float CIRCLEorangeX = 1425;
    float CIRCLEorangeY = 675;
    float alphaORANGE = 1.0f;
    Rectangle invisCIRCLEorange = {CIRCLEorangeX-80, CIRCLEorangeY-80, 160, 160};
    
    float CIRCLEpinkX = 1675;
    float CIRCLEpinkY = 675;
    float alphaPINK = 1.0f;    
    Rectangle invisCIRCLEpink = {CIRCLEpinkX-80, CIRCLEpinkY-80, 160, 160};
    
    float CIRCLEgrayX = 1425;
    float CIRCLEgrayY = 875;
    float alphaGRAY = 1.0f;    
    Rectangle invisCIRCLEgray = {CIRCLEgrayX-80, CIRCLEgrayY-80, 160, 160};
    
    float CIRCLEwhiteX = 1675;
    float CIRCLEwhiteY = 875;
    float alphaWHITE = 1.0f;
    Rectangle invisCIRCLEwhite = {CIRCLEwhiteX-80, CIRCLEwhiteY-80, 160, 160};
    
    float CIRCLEdeleteX = 1550;
    float CIRCLEdeleteY = 1000;
    float alphaDELETE = 1.0f;
    Rectangle invisCIRCLEdelete = {CIRCLEdeleteX-50, CIRCLEdeleteY-50, 100, 100};
    
    float deleteRecX = 1540;
    float deleteRecY = 975;
    
    Vector2 delTriang1 = {1550, 975};
    Vector2 delTriang2 = {1500, 1000};
    Vector2 delTriang3 = {1550, 1025};

    // CIRCLES ABOVE FOCUSBAR
    
    float tabCircleA1X = 400;
    float tabCircleA1Y = 840;
    
    float guessCircleA1X = 880;
    float guessCircleA1Y = 820;
    
    float alphaHalfVis = 0.75f;
    
    // ---------------------- INITIALIZATION ---------------------- //
    
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    ToggleBorderlessWindowed();
    InitWindow(screenWidth, screenHeight, "Mastermind");
    SetTargetFPS(60);
    
    // --------------------- GAME LOGIC --------------------------- //
    
    
    // TODO LIST :
    
    // Make game go back to main menu after everything
    // Smooth animation for showing colors, defined alphas, just make it work
    
    Color fBarColor1 = Fade(DARKGRAY, alphaDropShadow);
    Color fBarColor2 = Fade(DARKGRAY, alphaDropShadow);
    Color fBarColor3 = Fade(DARKGRAY, alphaDropShadow);
    Color fBarColor4 = Fade(DARKGRAY, alphaDropShadow);
    
    Color RedColor = RED;
    Color GreenColor = GREEN;
    Color BlueColor = BLUE;
    Color YellowColor = YELLOW;
    Color OrangeColor = ORANGE;
    Color PinkColor = PINK;
    Color GrayColor = GRAY;
    Color WhiteColor = WHITE;
    
    
    Color fBarArray[420] = { 
        fBarColor1, 
        fBarColor2, 
        fBarColor3, 
        fBarColor4     
    };
    
    // over focus bar circles
    
    Color tabColorA1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorA2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorA3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorA4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorB1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorB2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorB3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorB4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorC1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorC2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorC3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorC4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorD1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorD2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorD3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorD4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorE1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorE2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorE3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorE4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorF1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorF2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorF3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorF4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorG1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorG2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorG3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorG4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color tabColorH1 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorH2 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorH3 = Fade(DARKGRAY, alphaDropShadow);
    Color tabColorH4 = Fade(DARKGRAY, alphaDropShadow);    
    
    // Array for circle groups

    Color tabArray[9][5] = {
        {tabColorA1, tabColorA2, tabColorA3, tabColorA4},
        {tabColorB1, tabColorB2, tabColorB3, tabColorB4},
        {tabColorC1, tabColorC2, tabColorC3, tabColorC4},
        {tabColorD1, tabColorD2, tabColorD3, tabColorD4},
        {tabColorE1, tabColorE2, tabColorE3, tabColorE4},
        {tabColorF1, tabColorF2, tabColorF3, tabColorF4},
        {tabColorG1, tabColorG2, tabColorG3, tabColorG4},
        {tabColorH1, tabColorH2, tabColorH3, tabColorH4}
    };
    
    //// Alphas for them
    
    float AtabAlpha = 0.2f;
    float BtabAlpha = 0.2f;
    float CtabAlpha = 0.2f;
    float DtabAlpha = 0.2f;
    float EtabAlpha = 0.2f;
    float FtabAlpha = 0.2f;
    float GtabAlpha = 0.2f;
    float HtabAlpha = 0.2f;
    
    float tabAlphaArray[8] = {AtabAlpha, BtabAlpha, CtabAlpha, DtabAlpha, EtabAlpha, FtabAlpha, GtabAlpha, HtabAlpha};
    
    // Circles beside the input
    
    Color guessColorA1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorA2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorA3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorA4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorB1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorB2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorB3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorB4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorC1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorC2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorC3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorC4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorD1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorD2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorD3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorD4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorE1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorE2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorE3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorE4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorF1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorF2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorF3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorF4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorG1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorG2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorG3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorG4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessColorH1 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorH2 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorH3 = Fade(DARKGRAY, alphaDropShadow);
    Color guessColorH4 = Fade(DARKGRAY, alphaDropShadow);    
    
    Color guessArray[9][5] = {
        {guessColorA1, guessColorA2, guessColorA3, guessColorA4},
        {guessColorB1, guessColorB2, guessColorB3, guessColorB4},
        {guessColorC1, guessColorC2, guessColorC3, guessColorC4},
        {guessColorD1, guessColorD2, guessColorD3, guessColorD4},
        {guessColorE1, guessColorE2, guessColorE3, guessColorE4},
        {guessColorF1, guessColorF2, guessColorF3, guessColorF4},
        {guessColorG1, guessColorG2, guessColorG3, guessColorG4},
        {guessColorH1, guessColorH2, guessColorH3, guessColorH4}
    };   
        
    int currentFCircle = 0;
    
    RNG(1,8);
    
    //--------------------------------------------------------------------------------------

    Font font = LoadFont("pixantiqua.png");
    bool hasSubmitted = false;
    bool gameOver = false;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {  
        Vector2 MousePos = GetMousePosition();
        bool isHoveringPlayBtn = CheckCollisionPointRec(MousePos, invisPlayBtn);
        
        bool isHoveringNormalBtn = CheckCollisionPointRec(MousePos, invisNormalBtn);
        bool isHoveringAdvancedBtn = CheckCollisionPointRec(MousePos, invisAdvancedBtn);
        bool isHoveringZenBtn = CheckCollisionPointRec(MousePos, invisZenBtn);
        bool isHoveringEndlessBtn = CheckCollisionPointRec(MousePos, invisEndlessBtn);
        
        bool isHoveringSubmit = CheckCollisionPointRec(MousePos, invisSumbitBtn);
        
        bool isHoveringColorRed = CheckCollisionPointRec(MousePos, invisCIRCLEred);
        bool isHoveringColorGreen = CheckCollisionPointRec(MousePos, invisCIRCLEgreen);
        bool isHoveringColorBlue = CheckCollisionPointRec(MousePos, invisCIRCLEblue);
        bool isHoveringColorYellow = CheckCollisionPointRec(MousePos, invisCIRCLEyellow);
        bool isHoveringColorOrange = CheckCollisionPointRec(MousePos, invisCIRCLEorange);
        bool isHoveringColorPink = CheckCollisionPointRec(MousePos, invisCIRCLEpink);
        bool isHoveringColorGray = CheckCollisionPointRec(MousePos, invisCIRCLEgray);
        bool isHoveringColorWhite = CheckCollisionPointRec(MousePos, invisCIRCLEwhite);
        bool isHoveringColorDelete = CheckCollisionPointRec(MousePos, invisCIRCLEdelete);
        
        bool matchedRNG[4] = {false};
        bool matchedGUESS[4] = {false};
        
        // ------------------------- MAIN MENU AND GAMEMODE BUTTON HOVERING ---------------------------- //
        

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
        
        // --------------------------------- COLOR BUTTON HOVERING --------------------------------- //
        
        if (currentFCircle > 4) {
            currentFCircle--;
        }

            if (isHoveringColorRed && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = RED;
                currentFCircle++;
                addChar('1');
                
            } else if (isHoveringColorRed && gamemodeScreen == false && mainScreen == false) {
                alphaRED = 0.7f;
            } else {
                alphaRED = 1.0f;
            }       
            
            if (isHoveringColorGreen && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = GREEN;
                currentFCircle++;
                addChar('2');
                
            } else if (isHoveringColorGreen && gamemodeScreen == false && mainScreen == false) {
                alphaGREEN = 0.7f;
            } else {
                alphaGREEN = 1.0f;
            }      
            
            if (isHoveringColorBlue && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = BLUE;
                currentFCircle++;
                addChar('3');
                
            } else if (isHoveringColorBlue && gamemodeScreen == false && mainScreen == false) {
                alphaBLUE = 0.7f;
            } else {
                alphaBLUE = 1.0f;
            }           
            
            if (isHoveringColorYellow && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = YELLOW;
                currentFCircle++;
                addChar('4');
                
            } else if (isHoveringColorYellow && gamemodeScreen == false && mainScreen == false) {
                alphaYELLOW = 0.7f;
            } else {
                alphaYELLOW = 1.0f;
            }           
            
            if (isHoveringColorOrange && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = ORANGE;
                currentFCircle++;
                addChar('5');
                
            } else if (isHoveringColorOrange && gamemodeScreen == false && mainScreen == false) {
                alphaORANGE = 0.7f;
            } else {
                alphaORANGE = 1.0f;
            }           
            
            if (isHoveringColorPink && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = PINK;
                currentFCircle++;
                addChar('6');
                
            } else if (isHoveringColorPink && gamemodeScreen == false && mainScreen == false) {
                alphaPINK = 0.7f;
            } else {
                alphaPINK = 1.0f;
            }           
            
            if (isHoveringColorGray && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = GRAY;
                currentFCircle++;
                addChar('7');
                
            } else if (isHoveringColorGray && gamemodeScreen == false && mainScreen == false) {
                alphaGRAY = 0.7f;
            } else {
                alphaGRAY = 1.0f;
            }           
            
            if (isHoveringColorWhite && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = WHITE;
                currentFCircle++;
                addChar('8');
                
            } else if (isHoveringColorWhite && gamemodeScreen == false && mainScreen == false) {
                alphaWHITE = 0.7f;
            } else {
                alphaWHITE = 1.0f;
            }   
            
            if (isHoveringColorDelete && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false && currentFCircle > 0) {
                currentFCircle--;
                fBarArray[currentFCircle] = Fade(DARKGRAY, alphaDropShadow);
                deleteChar();
             
            } else if (isHoveringColorDelete && gamemodeScreen == false && mainScreen == false) {
                alphaDELETE = 0.7f;
            } else {
                alphaDELETE = 1.0f;
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
                DrawEllipse(CIRCLE1x, CIRCLE1y, 85, 85, fBarArray[0]);
                DrawEllipseLines(CIRCLE1x, CIRCLE1y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE1x, CIRCLE1y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE1x, CIRCLE1y, 87, 87, BLACK);
                
                DrawEllipse(CIRCLE2x, CIRCLE2y, 85, 85, fBarArray[1]);
                DrawEllipseLines(CIRCLE2x, CIRCLE2y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE2x, CIRCLE2y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE2x, CIRCLE2y, 87, 87, BLACK);
                
                DrawEllipse(CIRCLE3x, CIRCLE3y, 85, 85, fBarArray[2]);
                DrawEllipseLines(CIRCLE3x, CIRCLE3y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE3x, CIRCLE3y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE3x, CIRCLE3y, 87, 87, BLACK);
                
                DrawEllipse(CIRCLE4x, CIRCLE4y, 85, 85, fBarArray[3]);
                DrawEllipseLines(CIRCLE4x, CIRCLE4y, 85, 85, BLACK);
                DrawEllipseLines(CIRCLE4x, CIRCLE4y, 86, 86, BLACK);
                DrawEllipseLines(CIRCLE4x, CIRCLE4y, 87, 87, BLACK);
                
                /////////////
                //  ABOVE  //
                //  FOCUS  //
                // CIRCLES //
                /////////////
                
                // A - H (1)
                DrawEllipse(tabCircleA1X, tabCircleA1Y, 50, 50, tabArray[0][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-110, 50, 50, tabArray[1][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-110, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-110, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-110, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-220, 50, 50, tabArray[2][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-220, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-220, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-220, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-330, 50, 50, tabArray[3][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-330, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-330, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-330, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-440, 50, 50, tabArray[4][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-440, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-440, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-440, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-550, 50, 50, tabArray[5][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-550, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-550, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-550, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-660, 50, 50, tabArray[6][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-660, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-660, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-660, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X, tabCircleA1Y-770, 50, 50, tabArray[7][0]), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-770, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-770, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X, tabCircleA1Y-770, 53, 53, BLACK);                
                
                // A - H (2)
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y, 50, 50, tabArray[0][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-110, 50, 50, tabArray[1][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-110, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-110, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-110, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-220, 50, 50, tabArray[2][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-220, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-220, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-220, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-330, 50, 50, tabArray[3][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-330, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-330, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-330, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-440, 50, 50, tabArray[4][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-440, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-440, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-440, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-550, 50, 50, tabArray[5][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-550, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-550, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-550, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-660, 50, 50, tabArray[6][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-660, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-660, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-660, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+120, tabCircleA1Y-770, 50, 50, tabArray[7][1]), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-770, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-770, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+120, tabCircleA1Y-770, 53, 53, BLACK);                
                
                // A - H (3)
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y, 50, 50, tabArray[0][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-110, 50, 50, tabArray[1][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-110, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-110, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-110, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-220, 50, 50, tabArray[2][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-220, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-220, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-220, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-330, 50, 50, tabArray[3][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-330, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-330, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-330, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-440, 50, 50, tabArray[4][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-440, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-440, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-440, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-550, 50, 50, tabArray[5][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-550, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-550, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-550, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-660, 50, 50, tabArray[6][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-660, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-660, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-660, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+240, tabCircleA1Y-770, 50, 50, tabArray[7][2]), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-770, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-770, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+240, tabCircleA1Y-770, 53, 53, BLACK);               

                // A - H (4)
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y, 50, 50, tabArray[0][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-110, 50, 50, tabArray[1][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-110, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-110, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-110, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-220, 50, 50, tabArray[2][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-220, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-220, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-220, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-330, 50, 50, tabArray[3][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-330, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-330, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-330, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-440, 50, 50, tabArray[4][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-440, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-440, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-440, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-550, 50, 50, tabArray[5][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-550, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-550, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-550, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-660, 50, 50, tabArray[6][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-660, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-660, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-660, 53, 53, BLACK);
                
                DrawEllipse(tabCircleA1X+360, tabCircleA1Y-770, 50, 50, tabArray[7][3]), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-770, 51, 51, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-770, 52, 52, BLACK), DrawEllipseLines(tabCircleA1X+360, tabCircleA1Y-770, 53, 53, BLACK);                
                
                /////////////
                //  GUESS  //
                // CIRCLES //
                /////////////
                
                // 1 - 4 (A)
                DrawEllipse(guessCircleA1X, guessCircleA1Y, 10, 10, guessArray[0][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y, 10, 10, guessArray[0][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y+40, 10, 10, guessArray[0][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y+40, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y+40, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y+40, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y+40, 10, 10, guessArray[0][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y+40, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y+40, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y+40, 13, 13, BLACK);                
                
                
                // 1 - 4 (B)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-110, 10, 10, guessArray[1][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-110, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-110, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-110, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-110, 10, 10, guessArray[1][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-110, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-110, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-110, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-70, 10, 10, guessArray[1][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-70, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-70, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-70, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-70, 10, 10, guessArray[1][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-70, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-70, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-70, 13, 13, BLACK);                
                
                
                // 1 - 4 (C)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-220, 10, 10, guessArray[2][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-220, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-220, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-220, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-220, 10, 10, guessArray[2][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-220, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-220, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-220, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-180, 10, 10, guessArray[2][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-180, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-180, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-180, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-180, 10, 10, guessArray[2][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-180, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-180, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-180, 13, 13, BLACK);                
                
                
                // 1 - 4 (D)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-330, 10, 10, guessArray[3][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-330, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-330, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-330, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-330, 10, 10, guessArray[3][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-330, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-330, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-330, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-290, 10, 10, guessArray[3][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-290, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-290, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-290, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-290, 10, 10, guessArray[3][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-290, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-290, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-290, 13, 13, BLACK);                
                
                
                // 1 - 4 (E)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-440, 10, 10, guessArray[4][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-440, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-440, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-440, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-440, 10, 10, guessArray[4][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-440, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-440, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-440, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-400, 10, 10, guessArray[4][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-400, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-400, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-400, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-400, 10, 10, guessArray[4][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-400, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-400, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-400, 13, 13, BLACK);               


                // 1 - 4 (F)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-550, 10, 10, guessArray[5][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-550, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-550, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-550, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-550, 10, 10, guessArray[5][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-550, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-550, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-550, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-510, 10, 10, guessArray[5][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-510, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-510, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-510, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-510, 10, 10, guessArray[5][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-510, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-510, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-510, 13, 13, BLACK);                
                
                
                // 1 - 4 (G)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-660, 10, 10, guessArray[6][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-660, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-660, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-660, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-660, 10, 10, guessArray[6][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-660, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-660, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-660, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-620, 10, 10, guessArray[6][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-620, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-620, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-620, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-620, 10, 10, guessArray[6][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-620, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-620, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-620, 13, 13, BLACK);               


                // 1 - 4 (H)
                DrawEllipse(guessCircleA1X, guessCircleA1Y-770, 10, 10, guessArray[7][0]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-770, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-770, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-770, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-770, 10, 10, guessArray[7][1]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-770, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-770, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-770, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X, guessCircleA1Y-730, 10, 10, guessArray[7][2]), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-730, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-730, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X, guessCircleA1Y-730, 13, 13, BLACK);
                
                DrawEllipse(guessCircleA1X+40, guessCircleA1Y-730, 10, 10, guessArray[7][3]), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-730, 11, 11, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-730, 12, 12, BLACK), DrawEllipseLines(guessCircleA1X+40, guessCircleA1Y-730, 13, 13, BLACK);
                
                
                
                // SELECT BAR
                DrawRectangleRec(SelectBar, DARKGRAY);
                DrawTextEx(font, Title, posSelectBarText, SelectBarTextSize, 8, WHITE);
                
                DrawEllipse(CIRCLEredX, CIRCLEredY, 85, 85, Fade(RED, alphaRED));
                DrawEllipseLines(CIRCLEredX, CIRCLEredY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEredX, CIRCLEredY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEredX, CIRCLEredY, 87, 87, BLACK);
                DrawRectangleRec(invisCIRCLEred, Fade(BLACK, alphaInvis));

                DrawEllipse(CIRCLEgreenX, CIRCLEgreenY, 85, 85, Fade(GREEN, alphaGREEN));
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 87, 87, BLACK);
                DrawRectangleRec(invisCIRCLEgreen, Fade(BLACK, alphaInvis));
                
                DrawEllipse(CIRCLEblueX, CIRCLEblueY, 85, 85, Fade(BLUE, alphaBLUE));
                DrawEllipseLines(CIRCLEblueX, CIRCLEblueY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEblueX, CIRCLEblueY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEblueX, CIRCLEblueY, 87, 87, BLACK);     
                DrawRectangleRec(invisCIRCLEblue, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEyellowX, CIRCLEyellowY, 85, 85, Fade(YELLOW, alphaYELLOW));
                DrawEllipseLines(CIRCLEyellowX, CIRCLEyellowY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEyellowX, CIRCLEyellowY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEyellowX, CIRCLEyellowY, 87, 87, BLACK);      
                DrawRectangleRec(invisCIRCLEyellow, Fade(BLACK, alphaInvis));
                
                DrawEllipse(CIRCLEorangeX, CIRCLEorangeY, 85, 85, Fade(ORANGE, alphaORANGE));
                DrawEllipseLines(CIRCLEorangeX, CIRCLEorangeY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEorangeX, CIRCLEorangeY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEorangeX, CIRCLEorangeY, 87, 87, BLACK);   
                DrawRectangleRec(invisCIRCLEorange, Fade(BLACK, alphaInvis));
                
                DrawEllipse(CIRCLEpinkX, CIRCLEpinkY, 85, 85, Fade(PINK, alphaPINK));
                DrawEllipseLines(CIRCLEpinkX, CIRCLEpinkY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEpinkX, CIRCLEpinkY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEpinkX, CIRCLEpinkY, 87, 87, BLACK);
                DrawRectangleRec(invisCIRCLEpink, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEgrayX, CIRCLEgrayY, 85, 85, Fade(GRAY, alphaGRAY));
                DrawEllipseLines(CIRCLEgrayX, CIRCLEgrayY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEgrayX, CIRCLEgrayY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEgrayX, CIRCLEgrayY, 87, 87, BLACK);
                DrawRectangleRec(invisCIRCLEgray, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEwhiteX, CIRCLEwhiteY, 85, 85, Fade(WHITE, alphaWHITE));
                DrawEllipseLines(CIRCLEwhiteX, CIRCLEwhiteY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEwhiteX, CIRCLEwhiteY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEwhiteX, CIRCLEwhiteY, 87, 87, BLACK);
                DrawRectangleRec(invisCIRCLEwhite, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEdeleteX, CIRCLEdeleteY, 55, 55, Fade(GRAY, alphaDELETE));
                DrawRectangle(deleteRecX, deleteRecY, 50, 50, DARKGRAY);
                DrawTriangle(delTriang1, delTriang2, delTriang3, DARKGRAY);
                DrawTextEx(font, "X", (Vector2){1555, 982}, 40, 8, WHITE);
                DrawEllipseLines(CIRCLEdeleteX, CIRCLEdeleteY, 55, 55, BLACK);
                DrawEllipseLines(CIRCLEdeleteX, CIRCLEdeleteY, 56, 56, BLACK);
                DrawEllipseLines(CIRCLEdeleteX, CIRCLEdeleteY, 57, 57, BLACK);
                DrawRectangleRec(invisCIRCLEdelete, Fade(BLACK, alphaInvis));
                
                
                DrawEllipse(SubmitBtnX, SubmitBtnY, 55, 55, Fade(GREEN, alphaSubmit));
                DrawEllipseLines(SubmitBtnX, SubmitBtnY, 55, 55, DARKGRAY);
                DrawEllipseLines(SubmitBtnX, SubmitBtnY, 56, 56, DARKGRAY);
                DrawEllipseLines(SubmitBtnX, SubmitBtnY, 57, 57, DARKGRAY);
                DrawTextEx(font, "Submit", (Vector2){SubmitBtnX-50, SubmitBtnY-10}, 30, 4, Fade(WHITE, alphaVis));
                
                if (isHoveringSubmit && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false && currentFCircle == 4)) {
                
                    if (strcmp(storedMemoryBarArray[memBarCount], RNGnums) == 0) { // strcmp compares strings from the string.h library, not the usual comparison operator
                        printf("GAME FINISHED\n");
                        printf("User Input: %s\n", storedMemoryBarArray[memBarCount]);
                        printf("Correct Combo: %s\n", RNGnums);
                        fflush(stdout);
                        hasSubmitted = true;
                     
                    } else {
                        printf("User Input: %s\n", storedMemoryBarArray[memBarCount]);
                        currentFCircle = 0;
                        fBarArray[0] = Fade(DARKGRAY, alphaDropShadow), fBarArray[1] = Fade(DARKGRAY, alphaDropShadow), fBarArray[2] = Fade(DARKGRAY, alphaDropShadow), fBarArray[3] = Fade(DARKGRAY, alphaDropShadow);
                        
                        int tabCount = 0;
                        int tabRaiser = 0;
                        for (int i = 0; i < 4; i++) {
                            switch (storedMemoryBarArray[memBarCount][i]) {
                                case '1':
                                    tabArray[memBarCount][i] = Fade(RED, tabAlphaArray[memBarCount]);
                                    break;
                                case '2':
                                    tabArray[memBarCount][i] = Fade(GREEN, tabAlphaArray[memBarCount]);
                                    break;
                                case '3':
                                    tabArray[memBarCount][i] = Fade(BLUE, tabAlphaArray[memBarCount]);
                                    break;
                                case '4':
                                    tabArray[memBarCount][i] = Fade(YELLOW, tabAlphaArray[memBarCount]);
                                    break;
                                case '5':
                                    tabArray[memBarCount][i] = Fade(ORANGE, tabAlphaArray[memBarCount]);
                                    break;
                                case '6':
                                    tabArray[memBarCount][i] = Fade(PINK, tabAlphaArray[memBarCount]);
                                    break;
                                case '7':
                                    tabArray[memBarCount][i] = Fade(GRAY, tabAlphaArray[memBarCount]);
                                    break;
                                case '8':
                                    tabArray[memBarCount][i] = Fade(WHITE, tabAlphaArray[memBarCount]);
                                    break;
                            }
                            if (storedMemoryBarArray[memBarCount][i] == RNGnums[i]) {
                                guessArray[memBarCount][i] = RED;
                                matchedRNG[i] = true;
                                matchedGUESS[i] = true;
                            } else if (!matchedGUESS[i]) {
                                bool queried = false;
                                for (int j = 0; j < 4; j++) {
                                    if (!matchedRNG[j] && storedMemoryBarArray[memBarCount][i] == RNGnums[j]) {
                                        guessArray[memBarCount][i] = WHITE;
                                        matchedRNG[j] = true;
                                        matchedGUESS[i] = true;
                                        queried = true;
                                        break;
                                    }
                                }
                                if (!queried) {
                                    guessArray[memBarCount][i] = Fade(DARKGRAY, alphaDropShadow);
                                }
                            }
                            
                            printf("tabArray[%d][%d]: %d %d %d %d (R, G, B, A)\n",
                                   memBarCount, i,
                                   tabArray[memBarCount][i].r,
                                   tabArray[memBarCount][i].g,
                                   tabArray[memBarCount][i].b,
                                   tabArray[memBarCount][i].a);
                                   
                            printf("guessArray[%d][%d] color: R:%d G:%d B:%d A:%d\n", memBarCount, i,
                                    guessArray[memBarCount][i].r,
                                    guessArray[memBarCount][i].g,
                                    guessArray[memBarCount][i].b,
                                    guessArray[memBarCount][i].a);
                           
                        }
                        printf("Triggered, incorrect\n");
                        printf("NO. %d %f\n", memBarCount, tabAlphaArray[memBarCount]);
                        fflush(stdout);
                        
                        memBarCount++;
                        tabCount++;
                        tabRaiser++;
                        
                        if (tabAlphaArray[memBarCount] < 1) tabAlphaArray[memBarCount] += 0.02f; // change this line later
                        if (memBarCount >= 8) {
                            if (strcmp(storedMemoryBarArray[memBarCount], RNGnums) != 0) {
                                gameOver = true;
                            }
                        }
                        
                    }
                    
                } else if (isHoveringSubmit && gamemodeScreen == false && mainScreen == false) {
                    alphaSubmit = 0.5f;
                } else {
                    alphaSubmit = 0.8f;
                }
                
                if (hasSubmitted) {
                    DrawRectangle(0, 0, 2000, 2000, Fade(BLACK, alphaHalfVis));
                    DrawText("MYSTERY", 450, 350, 200, Fade(GOLD, alphaVis));
                    DrawText("SOLVED", 520, 550, 200, Fade(GOLD, alphaVis));
                }
                
                if (gameOver) {
                    DrawRectangle(0, 0, 2000, 2000, Fade(BLACK, alphaHalfVis));
                    DrawText("GAME", 640, 350, 200, Fade(GOLD, alphaVis));
                    DrawText("OVER", 630, 550, 200, Fade(GOLD, alphaVis));   
                }
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