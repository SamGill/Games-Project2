// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "Collisions";
const char GAME_TITLE[] = "Tank Banditos";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1200;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels

const int MAX_PLAYER_SHOTS = 10;
const int SHOT_TIME_BUFFER = 1;
const int MAX_ENEMY_TANKS = 7;

const int LONG_HZ_WALLS = 5;
const int SHORT_HZ_WALLS = 3;
const int LONG_VT_WALLS = 1;
const int SHORT_VT_WALLS = 3;

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 6.67428e-11f;             // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;
const int   TEXTURE_COLS = 4;           // texture has 4 columns
const int   RECTANGLE_START_FRAME = 0;  // rectangle starts at frame 0
const int   RECTANGLE_END_FRAME = 0;    // rectangle not animated
const int   SQUARE_START_FRAME = 1;     // square starts at frame 1
const int   SQUARE_END_FRAME = 1;       // square not animated
const int   CIRCLE_START_FRAME = 2;     // circle starts at frame 2
const int   CIRCLE_END_FRAME = 2;       // circle not animated
const int   SHIP_START_FRAME = 3;       // ship starts at frame 3
const int   SHIP_END_FRAME = 3;         // ship not animated
const int   LINE_START_FRAME = 4;       // line starts at frame 4
const int   LINE_END_FRAME = 4;         // line not animated
const float LINE_LENGTH = 32.0f;
const float LINE_SCALE  = 3.0f;         // this makes the line 96 pixels long

const RECT BULLET_RECTANGLE = {-16, -16, 16, 16};
const RECT WALL_RECTANGLE   = {-64, -64, 64, 64};
const RECT WALL_LONG_HZ_RECT = {-160, -16, 160, 16};
const RECT WALL_LONG_VT_RECT = {-80, -18, 80, 18};
const RECT WALL_SHORT_VT_RECT = {-18, -80, 18, 80};
const RECT WALL_SHORT_HZ_RECT = {-80, -18, 80, 18};
const RECT TANK_RECTANGLE   = {-167, -123, 167, 123};
const RECT POWERUP_RECT = {-16, -16, 16, 16};
const RECT ENEMY_BASE_RECT = {-32, -64, 32, 64};


const RECT  COLLISION_RECTANGLE = {-30,-16,30,16};
const RECT  COLLISION_BOX = {-30,-30,30,30};
const float   COLLISION_RADIUS = 29;

// graphic images
const char TEXTURES_IMAGE[] = "pictures\\textures.png";  // game textures
const char MENU_IMAGE[] =     "pictures\\menu.png";      // menu texture

const char TANK_BODY[]  =     "pictures\\tank_body.png";
const char TANK_HEAD[]  =     "pictures\\tank_head.png";

const char TANK_CRACK_ONE[] = "pictures\\tank_body2.png";
const char TANK_CRACK_TWO[] = "pictures\\tank_body3.png";
//const char TANK_CRACK_ONE[] = "pictures\\tank_body2.png";



const char BULLET_IMAGE[] =   "pictures\\bullet.png";
const char ENEMY_TANK[] =     "pictures\\enemy_tank.png";
const char WALL_LONG_HORIZONTAL[] = "pictures\\wall_long_horizontal.png";
const char WALL_LONG_VERTICAL[] = "pictures\\wall_long_vertical.png";
const char WALL_SHORT_HORIZONTAL[] = "pictures\\wall_short_horizontal.png";
const char WALL_SHORT_VERTICAL[] = "pictures\\wall_short_vertical.png";
const char WALL_IMAGE[] =     "pictures\\sand_background.png";
const char SAND_BACKGROUND[] = "pictures\\background.png";

const char POWER_UP[] =		  "pictures\\powerup.png";
const char ENEMY_BASE[] =	  "pictures\\enemy_base.png";


//Splash screen
const char SPLASH_SCREEN[] =  "pictures\\splash_screen.png";

//Game over screen
const char GAME_OVER[] =	  "pictures\\game_over.png";

//Menu screen
const char MENU_SCREEN[] =	  "pictures\\game_menu.png";

//Cheat code screen
const char CHEAT_SCREEN[] =	  "pictures\\cheat_codes.png";	

//Instructions code screen
const char INSTRUCTIONS[] =   "pictures\\instructions.png";

//Victory screen
const char VICTORY[] =		  "pictures\\high_score.png";

//Transition screen
const char TRANSITION[] =	  "pictures\\level2.png";

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
//const char WAVE_BANK[]  = "audio\\Win\\WavesExample1.xwb";
const char WAVE_BANK[] = "audio\\Win\\Project2_waveBank.xwb";
// SOUND_BANK must be location of .xsb file.
//const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";
const char SOUND_BANK[] = "audio\\Win\\project2_soundBank.xsb";

//Music
const char MAIN_MUSIC[] = "main_music";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR TANK_LEFT_KEY    = 0x41;     // left arrow
const UCHAR TANK_RIGHT_KEY   = 0x44;    // right arrow
const UCHAR TANK_UP_KEY      = 0x57;       // up arrow
const UCHAR TANK_DOWN_KEY    = 0x53;     // down arrow

// Pattern Step Action
enum PATTERN_STEP_ACTION {NONE, UP, DOWN, LEFT, RIGHT, TRACK, EVADE};

// States
enum GameStates {intro, gameMenu, cheatCodes, instructions, levelTransition, level_one, level_two, victory, gameover};

//Bullet type
enum bulletType {normal, mega};

#pragma region Level One Setup
const int wallOneX = 0;
const int wallOneY = 100;

const int wallTwoX = 600;
const int wallTwoY = 0;

const int wallThreeX = 1040;
const int wallThreeY = 100;

const int wallFourX = 500;
const int wallFourY = 150;

const int wallFiveX = 475;
const int wallFiveY = 150;

const int wallSixX = 315;
const int wallSixY = 200;

const int wallSevenX = 1040;
const int wallSevenY = 200;

const int wallEightX = 1040;
const int wallEightY = 300;

const int wallNineX = 0;
const int wallNineY = 350;

const int wallTenX = 540;
const int wallTenY = 372;

const int wallElevenX = 220;
const int wallElevenY = 500;

const int wallTwelveX = 880;
const int wallTwelveY = 600;

const int levelOnePlayerX = 10;
const int levelOnePlayerY = 10;


const int levelOneTankOneX = 20;
const int levelOneTankOneY = 120;
const int levelOneTankTwoX = 40;
const int levelOneTankTwoY = 250;
const int levelOneTankThreeX = 650;
const int levelOneTankThreeY = 50;
const int levelOneTankFourX = 50;
const int levelOneTankFourY = 380;
const int levelOneTankFiveX = 650;
const int levelOneTankFiveY = 200;
const int levelOneTankSixX = 700;
const int levelOneTankSixY = 450;
const int levelOneTankSevenX = 880;
const int levelOneTankSevenY = 325;

const int  JPO_COLS = 3;
const int  JPO_WIDTH = 512;
const int  JPO_HEIGHT = 512;
//JPO actions

#pragma endregion Level One Setup

#endif
