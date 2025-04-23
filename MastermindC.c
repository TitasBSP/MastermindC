#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

float alphaMain = 0.0f;

char storedMemoryBarArray[8][5];
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

    // ---------------------- INITIALIZATION ---------------------- //
    
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    ToggleBorderlessWindowed();
    
    InitWindow(screenWidth, screenHeight, "Mastermind");
    SetTargetFPS(60);
    
    // --------------------- GAME LOGIC --------------------------- //
    
    
    // TODO LIST :

    // Make all the circles if wrong
    // Check if color is correctly placed or selected
    // Game over if it reaches over 8
    
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
    
    // Arrays for circle groups
    
    Color AtabArray[420] = {
        tabColorA1,
        tabColorA2,
        tabColorA3,
        tabColorA4
    };        
    
    Color BtabArray[420] = {
        tabColorB1,
        tabColorB2,
        tabColorB3,
        tabColorB4
    };    
    
    Color CtabArray[420] = {
        tabColorC1,
        tabColorC2,
        tabColorC3,
        tabColorC4
    };    
    
    Color DtabArray[420] = {
        tabColorD1,
        tabColorD2,
        tabColorD3,
        tabColorD4
    };    
    
    Color EtabArray[420] = {
        tabColorE1,
        tabColorE2,
        tabColorE3,
        tabColorE4
    };    
    
    Color FtabArray[420] = {
        tabColorF1,
        tabColorF2,
        tabColorF3,
        tabColorF4
    };    
    
    Color GtabArray[420] = {
        tabColorG1,
        tabColorG2,
        tabColorG3,
        tabColorG4
    };    
    
    Color HtabArray[420] = {
        tabColorH1,
        tabColorH2,
        tabColorH3,
        tabColorH4
    };    
    
        
    int currentFCircle = 0;
    
    RNG(1,8);
    
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
        
        bool hasSubmitted = false;
        
        
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
                        
                        DrawText("GG", 1250, 900, 15, Fade(GOLD, alphaVis));
                     
                    } else {
                        printf("Triggered, incorrect\n");
                        memBarCount++;
                    }
                    

                } else if (isHoveringSubmit && gamemodeScreen == false && mainScreen == false) {
                    alphaSubmit = 0.5f;
                } else {
                    alphaSubmit = 0.8f;
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