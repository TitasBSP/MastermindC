#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "math.h"

#define max_balls 10000


// ██████╗░██████╗░███████╗░░░░░░░██████╗░░█████╗░███╗░░░███╗███████╗ ██╗░░░██╗░█████╗░██████╗░░██████╗
// ██╔══██╗██╔══██╗██╔════╝░░░░░░██╔════╝░██╔══██╗████╗░████║██╔════╝ ██║░░░██║██╔══██╗██╔══██╗██╔════╝
// ██████╔╝██████╔╝█████╗░░█████╗██║░░██╗░███████║██╔████╔██║█████╗░░ ╚██╗░██╔╝███████║██████╔╝╚█████╗░
// ██╔═══╝░██╔══██╗██╔══╝░░╚════╝██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░ ░╚████╔╝░██╔══██║██╔══██╗░╚═══██╗
// ██║░░░░░██║░░██║███████╗░░░░░░╚██████╔╝██║░░██║██║░╚═╝░██║███████╗ ░░╚██╔╝░░██║░░██║██║░░██║██████╔╝
// ╚═╝░░░░░╚═╝░░╚═╝╚══════╝░░░░░░░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝ ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░

float alphaMain = 0.0f; // Alpha for main menu, fade in 

char storedMemoryBarArray[9][5]; // 2D array which stores the character combinations for the 8 rows of colors which the player sees
int memBarCount = 0; // Any count here is used for counting up in a loop later on

int RNGcount = 0;
char RNGnums[5] = ""; // Stores RNG numbers from the RNG function

float alphaHalfVis = 0.5f;
float alphaQuarterVis = 0.25f;

Music backgroundMusic; // Defining a music variable which is used later on
bool musicPlaying = true;

// Timer variables

int timerLimit = 500;
int realTimer;
int secInterval = 1;

// Global variables for background spawning, aka the balls...

double recentSpawnTime = 0;
double timerSpawnTime = 0;
double spawnInterval = 1.5;

Vector2 spawnBalls[max_balls];
float ballSpeed[max_balls];
int ballRadius[max_balls];
Color ballColor[max_balls];

int ballCount = 0;

int spawnRNGcolor;
int screenHeight = 1080;

char timerText[4];
bool gameOver = false;


// ███████╗██╗░░░██╗███╗░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
// ██╔════╝██║░░░██║████╗░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
// █████╗░░██║░░░██║██╔██╗██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
// ██╔══╝░░██║░░░██║██║╚████║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
// ██║░░░░░╚██████╔╝██║░╚███║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
// ╚═╝░░░░░░╚═════╝░╚═╝░░╚══╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░

//-------------------------------------------------------------------------------------------|

void addCharRNG(char c) { // Used to add characters in an array which decided the combination
    int len = strlen(RNGnums);

    if (len < 4) {  // Ensure there's space for the new char (4 chars + 1 for '\0')
        RNGnums[len] = c;  // adds the new char
        RNGnums[len + 1] = '\0';  // null terminator to ensure nothing more is written.
    } else {
        printf("No space left to add another character.\n"); // Debugger
    }
}

void addChar(char c) { // Used to add characters in an array which displays colors
    int len = strlen(storedMemoryBarArray[memBarCount]);

    if (len < 4) {
        storedMemoryBarArray[memBarCount][len] = c;  
        storedMemoryBarArray[memBarCount][4] = '\0';
        RNGnums[4] = '\0';
    } else {
        printf("No space left to add another character.\n"); // Debugger
    }
}

void deleteChar() {
    int len = strlen(storedMemoryBarArray[memBarCount]);

    if (len == 0) {
        printf("Nothing to delete.\n"); // Debugger
        return;
    }

    storedMemoryBarArray[memBarCount][len - 1] = '\0';  // overwrite last character with null terminator
}

void RNG(int minNum, int maxNum) { // Function for RNG, minNum maxNum is customizable to allow the addition of multiple colors by other coders!
    
    memset(RNGnums, 0, sizeof(RNGnums)); // Resets RNGnums during a new call.
    
    for (int i = 0; i < 4; i++) { // Loops 4 times, value is randomized from min to max, in this case 1 - 8.
        int value = (rand() % maxNum) + minNum;
        char valueStr[2]; // Temporarily added to an array
        sprintf(valueStr, "%d", value); // Number converted to string to be able to be compared with the row submission
        addCharRNG(valueStr[0]); // The addCharRNG function is called which appends the characters from one array to another
    }
}

const char* ColorName(Color c) { // This whole thing is a debugger for colors, they used to be undefined. Leave this in case you're making custom gamemodes!
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

void ballSpawning() { // Function that handles the background spawning
    double currentTime = GetTime(); // Defining the time
    
    if ((currentTime - recentSpawnTime >= spawnInterval) && (ballCount < max_balls)) { // Ensures that the balls are spawned in the correct position and at the right time from the interval
        spawnBalls[ballCount] = (Vector2) {
            -100, 
            GetRandomValue(50, screenHeight - 50)
        };
        ballRadius[ballCount] = GetRandomValue(60, 125); // SIZE-dialer, customize to your liking
        ballSpeed[ballCount] = 150.0f; // SPEED-dialer, customize to your liking
        
        spawnRNGcolor = GetRandomValue(1,8);
        
        switch (spawnRNGcolor) { // RNG decides the color here
            case 1:
                ballColor[ballCount] = Fade(RED, alphaQuarterVis);
                break;
            case 2:
                ballColor[ballCount] = Fade(GREEN, alphaQuarterVis);
                break;
            case 3:
                ballColor[ballCount] = Fade(BLUE, alphaQuarterVis);
                break;
            case 4:
                ballColor[ballCount] = Fade(YELLOW, alphaQuarterVis);
                break;
            case 5:
                ballColor[ballCount] = Fade(ORANGE, alphaQuarterVis);
                break;
            case 6:
                ballColor[ballCount] = Fade(PINK, alphaQuarterVis);
                break;
            case 7:
                ballColor[ballCount] = Fade(GRAY, alphaQuarterVis);
                break;
            case 8:
                ballColor[ballCount] = Fade(WHITE, alphaQuarterVis);
                break;
        }
                
        ballCount++;
        recentSpawnTime = currentTime;
    }    
    
}

void Timer() { // Timer function when playing the game
    double stdTimer = GetTime(); // Grabs current time
    realTimer = ceil(stdTimer); // Rounds the time down for the most optimal experience
    
    if (!gameOver && (realTimer - timerSpawnTime >= secInterval)) {
        if (timerLimit > 0) { // Countdown...
            timerLimit--;
            timerSpawnTime = realTimer;
        }

    }
    
    sprintf(timerText, "%d", timerLimit);
}

void initMusic() { // Music initializer, customize your own music in the folder.
    InitAudioDevice();
    
    backgroundMusic = LoadMusicStream("Weird Fishes - Remixed.ogg");
    
    PlayMusicStream(backgroundMusic);
}

void updateSong() { // More readable function
    UpdateMusicStream(backgroundMusic);
}

void stopSong() { // More readable function
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}

//-------------------------------------------------------------------------------------------|


// ░██████╗░░█████╗░███╗░░░███╗███████╗ ░██████╗████████╗░█████╗░██████╗░████████╗░██████╗ ██╗░░██╗███████╗██████╗░███████╗
// ██╔════╝░██╔══██╗████╗░████║██╔════╝ ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝██╔════╝ ██║░░██║██╔════╝██╔══██╗██╔════╝
//  █║░░██╗░███████║██╔████╔██║█████╗░░ ╚█████╗░░░░██║░░░███████║██████╔╝░░░██║░░░╚█████╗░ ███████║█████╗░░██████╔╝█████╗░░
// ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░ ░╚═══██╗░░░██║░░░██╔══██║██╔══██╗░░░██║░░░░╚═══██╗ ██╔══██║██╔══╝░░██╔══██╗██╔══╝░░
// ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗ ██████╔╝░░░██║░░░██║░░██║██║░░██║░░░██║░░░██████╔╝ ██║░░██║███████╗██║░░██║███████╗
// ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝ ╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═════╝░ ╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚══════╝

int main(void)
{
    initMusic(); // Music starts here
    RNGnums[0] = '\0'; // RNG number array is reset
    
    // IMPORTANT TOGGLES FOR PLAYTESTING AND EFFICIENCY //
    
    bool mainScreen = false;
    bool gamemodeScreen = false;
    
    bool startingScreen = false;
    
    bool normalScreen = true;
    bool advancedScreen = false;
    bool zenScreen = false;
    bool endlessScreen = false;
    
    //-------------------------------------------------//
    
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
    
    // ---------------------- GAMEMODE SCREEN --------------------- //
    
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
    
    float alphaBtnFadeIn = 0.0f;
    
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
    
    Vector2 posRetryFinish = {1080, 645};
    Vector2 posRetryFinishBlack = {1082, 650};
    Vector2 posMainFinish = {390, 655};
    Vector2 posMainFinishBlack = {394, 660};
    
    Rectangle invisRetry = {980, 595, 450, 200};
    Rectangle invisMainMenu = {380, 595, 450, 200};
    
    Vector2 posTimeRemain = {1065, 60};
    
    // ---------------------- INITIALIZATION ---------------------- //
    
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    ToggleBorderlessWindowed();
    InitWindow(screenWidth, screenHeight, "Mastermind");
    SetTargetFPS(60);
    
    // --------------------- GAME LOGIC --------------------------- //
    
    // ████████╗░█████╗░░░░░░░██████╗░░█████╗░ ██╗░░░░░██╗░██████╗████████╗██╗
    // ╚══██╔══╝██╔══██╗░░░░░░██╔══██╗██╔══██╗ ██║░░░░░██║██╔════╝╚══██╔══╝╚═╝
    // ░░░██║░░░██║░░██║█████╗██║░░██║██║░░██║ ██║░░░░░██║╚█████╗░░░░██║░░░░░░
    // ░░░██║░░░██║░░██║╚════╝██║░░██║██║░░██║ ██║░░░░░██║░╚═══██╗░░░██║░░░░░░
    // ░░░██║░░░╚█████╔╝░░░░░░██████╔╝╚█████╔╝ ███████╗██║██████╔╝░░░██║░░░██╗
    // ░░░╚═╝░░░░╚════╝░░░░░░░╚═════╝░░╚════╝░ ╚══════╝╚═╝╚═════╝░░░░╚═╝░░░╚═╝
    
    //////////////////////////////////////////////////////////////////////////
    // 
    // * Music (main menu done), do game now, add a volume changer with keys  
    // 
    // * Add instructions
    //
    //
    //////////////////////////////////////////////////////////////////////////
    
    // Focus bar colors 
    
    Color fBarColor1 = Fade(DARKGRAY, alphaDropShadow);
    Color fBarColor2 = Fade(DARKGRAY, alphaDropShadow);
    Color fBarColor3 = Fade(DARKGRAY, alphaDropShadow);
    Color fBarColor4 = Fade(DARKGRAY, alphaDropShadow);
    
    Color fBarArray[420] = { 
        fBarColor1, 
        fBarColor2, 
        fBarColor3, 
        fBarColor4     
    };
    
    // Tab Circle Colors
    
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
    
    // Array for circle rows

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
    
    //// Alphas for tabs
    
    float AtabAlpha = 0.2f;
    float BtabAlpha = 0.2f;
    float CtabAlpha = 0.2f;
    float DtabAlpha = 0.2f;
    float EtabAlpha = 0.2f;
    float FtabAlpha = 0.2f;
    float GtabAlpha = 0.2f;
    float HtabAlpha = 0.2f;
    
    float tabAlphaArray[8] = {AtabAlpha, BtabAlpha, CtabAlpha, DtabAlpha, EtabAlpha, FtabAlpha, GtabAlpha, HtabAlpha};
    
    // Circles beside the tab, for guessing
    
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
        
    int currentFCircle = 0; // Count for changing between tabs
    
    RNG(1,8); // RNG command
    
    //--------------------------------------------------------------------------------------|

    Font font = LoadFont("pixantiqua.png"); // Font loader, customize to your liking
    bool hasSubmitted = false;
    bool gameOver = false;

    // ░██████╗░░█████╗░███╗░░░███╗███████╗ ██╗░░░░░░█████╗░░█████╗░██████╗░
    // ██╔════╝░██╔══██╗████╗░████║██╔════╝ ██║░░░░░██╔══██╗██╔══██╗██╔══██╗
    // ██║░░██╗░███████║██╔████╔██║█████╗░░ ██║░░░░░██║░░██║██║░░██║██████╔╝
    // ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░ ██║░░░░░██║░░██║██║░░██║██╔═══╝░
    // ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗ ███████╗╚█████╔╝╚█████╔╝██║░░░░░
    // ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝ ╚══════╝░╚════╝░░╚════╝░╚═╝░░░░░
    
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {  
        updateSong(); // Updates the song so it stays consistent during gameplay
        
        float moveTime = GetFrameTime();
        
        // BOOLEANS FOR GAME HITBOXES
    
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
        
        bool isHoveringMainMenu = CheckCollisionPointRec(MousePos, invisMainMenu);
        bool isHoveringRetry = CheckCollisionPointRec(MousePos, invisRetry);
        
        // BOOLEANS FOR COLORS
        
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
            int pressedKey = GetCharPressed();
            
            if ((isHoveringColorRed && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '1') && gamemodeScreen == false && mainScreen == false) { // Selecting can be done with both mouse or keyboard inputs
                currentFCircle++;
                addChar('1');
                
            } else if (isHoveringColorRed && gamemodeScreen == false && mainScreen == false) {
                alphaRED = 0.7f;
            } else {
                alphaRED = 1.0f;
            }       
            
            if ((isHoveringColorGreen && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '2') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = GREEN;
                currentFCircle++;
                addChar('2');
                
            } else if (isHoveringColorGreen && gamemodeScreen == false && mainScreen == false) {
                alphaGREEN = 0.7f;
            } else {
                alphaGREEN = 1.0f;
            }      
            
            if ((isHoveringColorBlue && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '3') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = BLUE;
                currentFCircle++;
                addChar('3');
                
            } else if (isHoveringColorBlue && gamemodeScreen == false && mainScreen == false) {
                alphaBLUE = 0.7f;
            } else {
                alphaBLUE = 1.0f;
            }           
            
            if ((isHoveringColorYellow && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '4') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = YELLOW;
                currentFCircle++;
                addChar('4');
                
            } else if (isHoveringColorYellow && gamemodeScreen == false && mainScreen == false) {
                alphaYELLOW = 0.7f;
            } else {
                alphaYELLOW = 1.0f;
            }           
            
            if ((isHoveringColorOrange && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '5') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = ORANGE;
                currentFCircle++;
                addChar('5');
                
            } else if (isHoveringColorOrange && gamemodeScreen == false && mainScreen == false) {
                alphaORANGE = 0.7f;
            } else {
                alphaORANGE = 1.0f;
            }           
            
            if ((isHoveringColorPink && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '6') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = PINK;
                currentFCircle++;
                addChar('6');
                
            } else if (isHoveringColorPink && gamemodeScreen == false && mainScreen == false) {
                alphaPINK = 0.7f;
            } else {
                alphaPINK = 1.0f;
            }           
            
            if ((isHoveringColorGray && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '7') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = GRAY;
                currentFCircle++;
                addChar('7');
                
            } else if (isHoveringColorGray && gamemodeScreen == false && mainScreen == false) {
                alphaGRAY = 0.7f;
            } else {
                alphaGRAY = 1.0f;
            }           
            
            if ((isHoveringColorWhite && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (pressedKey == '8') && gamemodeScreen == false && mainScreen == false) {
                fBarArray[currentFCircle] = WHITE;
                currentFCircle++;
                addChar('8');
                
            } else if (isHoveringColorWhite && gamemodeScreen == false && mainScreen == false) {
                alphaWHITE = 0.7f;
            } else {
                alphaWHITE = 1.0f;
            }   
            
            if ((isHoveringColorDelete && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (IsKeyPressed(KEY_BACKSPACE)) && gamemodeScreen == false && mainScreen == false && currentFCircle > 0) {
                currentFCircle--;
                fBarArray[currentFCircle] = Fade(DARKGRAY, alphaDropShadow);
                deleteChar();
             
            } else if (isHoveringColorDelete && gamemodeScreen == false && mainScreen == false) {
                alphaDELETE = 0.7f;
            } else {
                alphaDELETE = 1.0f;
            }                   
            
        // The visible stuff on screen
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            if (mainScreen) { // Happens under main menu
                if (alphaMain < 1) alphaMain += 0.03f;
                
                ballSpawning();
                
                for (int i = 0; i < ballCount; i++) {
                    spawnBalls[i].x += ballSpeed[i] * moveTime;
                }
    
                for (int i = 0; i < ballCount; i++) {
                    DrawCircleV(spawnBalls[i], ballRadius[i], ballColor[i]);
                }
                
                DrawTextEx(font, Title, posTitle, TitleSize, 15, Fade(GOLD, alphaMain)); // OBS! Order of operators: (Font var, string var, position var, SIZE, KERNING, COLOR);
                DrawEllipse(PlayBtnX, PlayBtnY, 250, 100, Fade(GOLD, alphaMain));
                DrawRectangleRec(invisPlayBtn, Fade(WHITE, alphaInvis));
                DrawTextEx(font, PlayText, posPlayShdw, PlayTextSize, 8, Fade(BLACK, alphaMain));
                DrawTextEx(font, PlayText, posPlayText, PlayTextSize, 8, Fade(WHITE, alphaMain));
            }
            
            if (gamemodeScreen) { // Happens under gamemode menu
                
                ballSpawning();
                
                for (int i = 0; i < ballCount; i++) {
                    spawnBalls[i].x += ballSpeed[i] * moveTime;
                }
                
                for (int i = 0; i < ballCount; i++) {
                    DrawCircleV(spawnBalls[i], ballRadius[i], ballColor[i]);
                }
                
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
            
            if (startingScreen) { // 3-2-1-GO Screen
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
            
            if (normalScreen) { // Normal GAMEMODE code
        
                ballSpawning();

                for (int i = 0; i < ballCount; i++) { // Background moving along the x-axis
                    spawnBalls[i].x += ballSpeed[i] * moveTime;
                }
                
                for (int i = 0; i < ballCount; i++) { // Drawing the balls
                    DrawCircleV(spawnBalls[i], ballRadius[i], ballColor[i]);
                }
                
                Timer();
     
                if (timerLimit <= 0) { // Game over when timer is 0 or less
                    gameOver = true;
                    normalScreen = false;
                }
                
                DrawRectangleRec(DropShadow, Fade(DARKGRAY, alphaDropShadow));
                
                DrawRectangle(1060, 30, 175, 120, Fade(GRAY, alphaDropShadow));
                DrawTextEx(font, "Time Remaining", posTimeRemain, 20, 3, WHITE);
                DrawText(timerText, 1105, 90, 50, WHITE);
                
                
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
                DrawText("1", CIRCLEredX-15, CIRCLEredY-45, 100, Fade(BLACK, alphaQuarterVis));
                DrawRectangleRec(invisCIRCLEred, Fade(BLACK, alphaInvis));

                DrawEllipse(CIRCLEgreenX, CIRCLEgreenY, 85, 85, Fade(GREEN, alphaGREEN));
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEgreenX, CIRCLEgreenY, 87, 87, BLACK);
                DrawText("2", CIRCLEgreenX-25, CIRCLEgreenY-45, 100, Fade(BLACK, alphaQuarterVis));
                DrawRectangleRec(invisCIRCLEgreen, Fade(BLACK, alphaInvis));
                
                DrawEllipse(CIRCLEblueX, CIRCLEblueY, 85, 85, Fade(BLUE, alphaBLUE));
                DrawEllipseLines(CIRCLEblueX, CIRCLEblueY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEblueX, CIRCLEblueY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEblueX, CIRCLEblueY, 87, 87, BLACK);
                DrawText("3", CIRCLEblueX-25, CIRCLEblueY-45, 100, Fade(BLACK, alphaQuarterVis));                
                DrawRectangleRec(invisCIRCLEblue, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEyellowX, CIRCLEyellowY, 85, 85, Fade(YELLOW, alphaYELLOW));
                DrawEllipseLines(CIRCLEyellowX, CIRCLEyellowY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEyellowX, CIRCLEyellowY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEyellowX, CIRCLEyellowY, 87, 87, BLACK);  
                DrawText("4", CIRCLEyellowX-25, CIRCLEyellowY-45, 100, Fade(BLACK, alphaQuarterVis));
                DrawRectangleRec(invisCIRCLEyellow, Fade(BLACK, alphaInvis));
                
                DrawEllipse(CIRCLEorangeX, CIRCLEorangeY, 85, 85, Fade(ORANGE, alphaORANGE));
                DrawEllipseLines(CIRCLEorangeX, CIRCLEorangeY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEorangeX, CIRCLEorangeY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEorangeX, CIRCLEorangeY, 87, 87, BLACK);
                DrawText("5", CIRCLEorangeX-25, CIRCLEorangeY-45, 100, Fade(BLACK, alphaQuarterVis));
                DrawRectangleRec(invisCIRCLEorange, Fade(BLACK, alphaInvis));
                
                DrawEllipse(CIRCLEpinkX, CIRCLEpinkY, 85, 85, Fade(PINK, alphaPINK));
                DrawEllipseLines(CIRCLEpinkX, CIRCLEpinkY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEpinkX, CIRCLEpinkY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEpinkX, CIRCLEpinkY, 87, 87, BLACK);
                DrawText("6", CIRCLEpinkX-25, CIRCLEpinkY-45, 100, Fade(BLACK, alphaQuarterVis));
                DrawRectangleRec(invisCIRCLEpink, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEgrayX, CIRCLEgrayY, 85, 85, Fade(GRAY, alphaGRAY));
                DrawEllipseLines(CIRCLEgrayX, CIRCLEgrayY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEgrayX, CIRCLEgrayY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEgrayX, CIRCLEgrayY, 87, 87, BLACK);
                DrawText("7", CIRCLEgrayX-25, CIRCLEgrayY-45, 100, Fade(BLACK, alphaQuarterVis));
                DrawRectangleRec(invisCIRCLEgray, Fade(BLACK, alphaInvis));                
                
                DrawEllipse(CIRCLEwhiteX, CIRCLEwhiteY, 85, 85, Fade(WHITE, alphaWHITE));
                DrawEllipseLines(CIRCLEwhiteX, CIRCLEwhiteY, 85, 85, BLACK);
                DrawEllipseLines(CIRCLEwhiteX, CIRCLEwhiteY, 86, 86, BLACK);
                DrawEllipseLines(CIRCLEwhiteX, CIRCLEwhiteY, 87, 87, BLACK);
                DrawText("8", CIRCLEwhiteX-25, CIRCLEwhiteY-45, 100, Fade(BLACK, alphaQuarterVis));
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
                
                if ((isHoveringSubmit && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (IsKeyPressed(KEY_ENTER)) && gamemodeScreen == false && mainScreen == false && currentFCircle == 4)) { // IF-statement for submit button
                    
                    if (strcmp(storedMemoryBarArray[memBarCount], RNGnums) == 0) { // strcmp compares strings from the string.h library, not the usual comparison operator
                        // GAME IS FINISHED IF THE STRINGS ARE IDENTICAL
                        printf("GAME FINISHED\n"); // Debugger
                        printf("User Input: %s\n", storedMemoryBarArray[memBarCount]);
                        printf("Correct Combo: %s\n", RNGnums);
                        fflush(stdout);
                        hasSubmitted = true;
                     
                    } else { // If game is not finished
                        if (tabAlphaArray[memBarCount] < 1) tabAlphaArray[memBarCount] += 0.02f; // change this line later
                        printf("User Input: %s\n", storedMemoryBarArray[memBarCount]);
                        currentFCircle = 0;
                        fBarArray[0] = Fade(DARKGRAY, alphaDropShadow), fBarArray[1] = Fade(DARKGRAY, alphaDropShadow), fBarArray[2] = Fade(DARKGRAY, alphaDropShadow), fBarArray[3] = Fade(DARKGRAY, alphaDropShadow); // Resets the focus bar to be gray
                        
                        int tabCount = 0;
                        int tabRaiser = 0;
                        
                        for (int i = 0; i < 4; i++) { // Runs a loop which appends the strings into a tab array above and converts the strings into colors which the player can see
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
                            if (storedMemoryBarArray[memBarCount][i] == RNGnums[i]) { // System for deciding if a color is correct and placed right, or if it's correct but the placement is false, or if it's neither
                                guessArray[memBarCount][i] = RED; // When correctly placed and color is right
                                matchedRNG[i] = true;
                                matchedGUESS[i] = true;
                            } else if (!matchedGUESS[i]) {
                                bool queried = false;
                                for (int j = 0; j < 4; j++) { // When incorrectly placed but color is right
                                    if (!matchedRNG[j] && storedMemoryBarArray[memBarCount][i] == RNGnums[j]) {
                                        guessArray[memBarCount][i] = WHITE;
                                        matchedRNG[j] = true;
                                        matchedGUESS[i] = true;
                                        queried = true;
                                        break;
                                    }
                                }
                                if (!queried) { // When it's neither correctly placed nor color is right
                                    guessArray[memBarCount][i] = Fade(DARKGRAY, alphaDropShadow);
                                    matchedRNG[i] = false;
                                    matchedGUESS[i] = false;   
                                }
                            }
                            
                            printf("tabArray[%d][%d]: %d %d %d %d (R, G, B, A)\n", // DEBUGGER for tabs
                                   memBarCount, i,
                                   tabArray[memBarCount][i].r,
                                   tabArray[memBarCount][i].g,
                                   tabArray[memBarCount][i].b,
                                   tabArray[memBarCount][i].a);
                                   
                            printf("guessArray[%d][%d] color: R:%d G:%d B:%d A:%d\n", memBarCount, i, // DEBUGGER for guess dots
                                    guessArray[memBarCount][i].r,
                                    guessArray[memBarCount][i].g,
                                    guessArray[memBarCount][i].b,
                                    guessArray[memBarCount][i].a);
                           
                        }
                        printf("Triggered, incorrect\n"); // Debugger for combinations
                        printf("NO. %d %f\n", memBarCount, tabAlphaArray[memBarCount]);
                        fflush(stdout);
                        
                        memBarCount++;
                        tabCount++;
                        tabRaiser++;
                      
                        if (memBarCount >= 8) { // Game over is triggered if a tab above 8 is opened
                            if (strcmp(storedMemoryBarArray[memBarCount - 1], RNGnums) != 0) {
                                gameOver = true;
                                normalScreen = false;
                                gamemodeScreen = false;
                                mainScreen = false;
                                startingScreen = false;
                            }
                        }
                        
                    }
                    
                } else if (isHoveringSubmit && gamemodeScreen == false && mainScreen == false) {
                    alphaSubmit = 0.5f;
                } else {
                    alphaSubmit = 0.8f;
                }
                
                if (hasSubmitted) { // Confirms level complete when correct combination is submitted
                    printf("Have you submitted? %d", hasSubmitted);
                    fflush(stdout);
                    
                    normalScreen = false;
                    gamemodeScreen = false;
                    mainScreen = false;
                    startingScreen = false;
                    
                    hasSubmitted = false;
                    
                }
               
            }
            
            if (!normalScreen && !gamemodeScreen && !mainScreen && !startingScreen && !gameOver) { // LEVEL COMPLETE SCREEN, a lot of resetting...
                if (alphaBtnFadeIn < 1) alphaBtnFadeIn += 0.02f;
                fBarArray[0] = Fade(DARKGRAY, alphaDropShadow), fBarArray[1] = Fade(DARKGRAY, alphaDropShadow), fBarArray[2] = Fade(DARKGRAY, alphaDropShadow), fBarArray[3] = Fade(DARKGRAY, alphaDropShadow);
                
                DrawRectangle(0, 0, 2000, 2000, Fade(BLACK, alphaHalfVis));
                
                DrawText("MYSTERY", 420, 150, 200, Fade(GOLD, alphaBtnFadeIn));
                DrawText("SOLVED", 500, 350, 200, Fade(GOLD, alphaBtnFadeIn));
                
                DrawEllipse(610, 700, 250, 100, Fade(GOLD, alphaBtnFadeIn));
                DrawEllipse(1210, 700, 250, 100, Fade(GOLD, alphaBtnFadeIn));
                
                DrawRectangleRec(invisRetry, Fade(RED, alphaInvis));
                DrawRectangleRec(invisMainMenu, Fade(RED, alphaInvis));
                
                
                DrawTextEx(font, "Retry", posRetryFinishBlack, 103, 10, Fade(BLACK, alphaBtnFadeIn));
                DrawTextEx(font, "Retry", posRetryFinish, 100, 10, Fade(WHITE, alphaBtnFadeIn));
                
                DrawTextEx(font, "Main Menu", posMainFinishBlack, 80, 10, Fade(BLACK, alphaBtnFadeIn));
                DrawTextEx(font, "Main Menu", posMainFinish, 80, 10, Fade(WHITE, alphaBtnFadeIn));

                if (isHoveringRetry && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) { // When clicking retry button
                    timerLimit = 500;
                    hasSubmitted = false;
                    startingScreen = true;
                    memBarCount = 0;
                    RNGcount = 0;
                    currentFCircle = 0;
                    gameOver = false;
                    RNG(1,8);
                    
                    // Resetting alphas
                    tabAlphaArray[memBarCount] = 0.0f;
                    alphaBtnFadeIn = 0.0f;
                    alphaNUM3 = 0.0f; alphaNUM2 = 0.0f; alphaNUM1 = 0.0f; alphaGO = 0.0f;             
                    
                    for (int i = 0; i < 5; i++) {
                        deleteChar();
                    }
                    
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 4; j++) {
                            tabArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            guessArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            storedMemoryBarArray[i][j] = '\0';
                        }
                    }     
                 
                } else if (isHoveringRetry && gamemodeScreen == false && mainScreen == false) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                } else {
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                }  
                
                if (isHoveringMainMenu && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) { // When clicking main menu button
                    timerLimit = 500;
                    hasSubmitted = false;
                    mainScreen = true;
                    memBarCount = 0;
                    RNGcount = 0;
                    currentFCircle = 0;
                    gameOver = false;
                    
                    // Resetting alphas
                    alphaMain = 0.0f;
                    alphaGamemode = 0.0f;
                    tabAlphaArray[memBarCount] = 0.0f;
                    alphaBtnFadeIn = 0.0f;
                    alphaNUM3 = 0.0f; alphaNUM2 = 0.0f; alphaNUM1 = 0.0f; alphaGO = 0.0f;
                    RNG(1,8);
                    fflush(stdout);                
                    
                    for (int i = 0; i < 5; i++) {
                        deleteChar();
                    }
                    
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 4; j++) {
                            tabArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            guessArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            storedMemoryBarArray[i][j] = '\0';
                        }
                    }     
                 
                } else if (isHoveringMainMenu && gamemodeScreen == false && mainScreen == false) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                } else {
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                }  
            } else if (!normalScreen && !gamemodeScreen && !mainScreen && !startingScreen && gameOver) { // GAME OVER screen, practically identical except for output
                if (alphaBtnFadeIn < 1) alphaBtnFadeIn += 0.02f;
                fBarArray[0] = Fade(DARKGRAY, alphaDropShadow), fBarArray[1] = Fade(DARKGRAY, alphaDropShadow), fBarArray[2] = Fade(DARKGRAY, alphaDropShadow), fBarArray[3] = Fade(DARKGRAY, alphaDropShadow);
                
                DrawRectangle(0, 0, 2000, 2000, Fade(BLACK, alphaQuarterVis));
                
                DrawText("GAME", 480, 50, 300, Fade(GOLD, alphaBtnFadeIn));
                DrawText("OVER", 480, 300, 300, Fade(GOLD, alphaBtnFadeIn));
                
                DrawEllipse(610, 700, 250, 100, Fade(GOLD, alphaBtnFadeIn));
                DrawEllipse(1210, 700, 250, 100, Fade(GOLD, alphaBtnFadeIn));
                
                DrawRectangleRec(invisRetry, Fade(RED, alphaInvis));
                DrawRectangleRec(invisMainMenu, Fade(RED, alphaInvis));
                
                
                DrawTextEx(font, "Retry", posRetryFinishBlack, 103, 10, Fade(BLACK, alphaBtnFadeIn));
                DrawTextEx(font, "Retry", posRetryFinish, 100, 10, Fade(WHITE, alphaBtnFadeIn));
                
                DrawTextEx(font, "Main Menu", posMainFinishBlack, 80, 10, Fade(BLACK, alphaBtnFadeIn));
                DrawTextEx(font, "Main Menu", posMainFinish, 80, 10, Fade(WHITE, alphaBtnFadeIn));

                if (isHoveringRetry && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                    timerLimit = 500;
                    hasSubmitted = false;
                    startingScreen = true;
                    memBarCount = 0;
                    RNGcount = 0;
                    currentFCircle = 0;
                    gameOver = false;
                    RNG(1,8);
                    
                    // Resetting alphas
                    tabAlphaArray[memBarCount] = 0.0f;
                    alphaBtnFadeIn = 0.0f;
                    alphaNUM3 = 0.0f; alphaNUM2 = 0.0f; alphaNUM1 = 0.0f; alphaGO = 0.0f;             
                    
                    for (int i = 0; i < 5; i++) {
                        deleteChar();
                    }
                    
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 4; j++) {
                            tabArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            guessArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            storedMemoryBarArray[i][j] = '\0';
                        }
                    }     
                 
                } else if (isHoveringRetry && gamemodeScreen == false && mainScreen == false) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                } else {
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                }  
                
                if (isHoveringMainMenu && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gamemodeScreen == false && mainScreen == false) {
                    timerLimit = 500;
                    hasSubmitted = false;
                    mainScreen = true;
                    memBarCount = 0;
                    RNGcount = 0;
                    currentFCircle = 0;
                    gameOver = false;
                    
                    // Resetting alphas
                    alphaMain = 0.0f;
                    alphaGamemode = 0.0f;
                    tabAlphaArray[memBarCount] = 0.0f;
                    alphaBtnFadeIn = 0.0f;
                    alphaNUM3 = 0.0f; alphaNUM2 = 0.0f; alphaNUM1 = 0.0f; alphaGO = 0.0f;
                    RNG(1,8);
                    fflush(stdout);                
                    
                    for (int i = 0; i < 5; i++) {
                        deleteChar();
                    }
                    
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 4; j++) {
                            tabArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            guessArray[i][j] = Fade(DARKGRAY, alphaDropShadow);
                            storedMemoryBarArray[i][j] = '\0';
                        }
                    }     
                 
                } else if (isHoveringMainMenu && gamemodeScreen == false && mainScreen == false) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                } else {
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                }  
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    stopSong();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}