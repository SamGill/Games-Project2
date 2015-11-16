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
const UINT GAME_HEIGHT = 700;               // height of game in pixels

const int NUM_ENEMY_BULLETS = 6;
const int MAX_PLAYER_SHOTS = 10;
const int SHOT_TIME_BUFFER = 1;
const int MAX_ENEMY_TANKS = 7;
const int NUM_LVL_TWO_HZ_WALL = 4;
const int NUM_LVL_TWO_VT_WALL = 3;

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
//const RECT TANK_RECTANGLE   = {-106, -106, 220, 200};
const RECT WALL_LONG_HZ_RECT = {-160, -16, 160, 16};
const RECT TANK_RECTANGLE   = {-167, -123, 167, 123};

const RECT WALL_SHORT_HZ_RECT = {-80, -17, 80, 17};
const RECT WALL_SHORT_VT_RECT = {-17, -80, 17, 80};


const RECT  COLLISION_RECTANGLE = {-30,-16,30,16};
const RECT  COLLISION_BOX = {-30,-30,30,30};
const float   COLLISION_RADIUS = 29;

// graphic images
const char TEXTURES_IMAGE[] = "pictures\\textures.png";  // game textures
const char MENU_IMAGE[] =     "pictures\\menu.png";      // menu texture

const char TANK_BODY[]  =     "pictures\\tank_body.png";
const char TANK_HEAD[]  =     "pictures\\tank_head.png";
const char BULLET_IMAGE[] =   "pictures\\bullet.png";
const char ENEMY_TANK[] =     "pictures\\enemy_tank.png";
const char WALL_LONG_HORIZONTAL[] = "pictures\\wall_long_horizontal.png";
const char WALL_LONG_VERTICAL[] = "pictures\\wall_long_vertical.png";
const char WALL_SHORT_HORIZONTAL[] = "pictures\\wall_short_horizontal.png";
const char WALL_SHORT_VERTICAL[] = "pictures\\wall_short_vertical.png";
const char WALL_IMAGE[] =     "pictures\\sand_background.png";
const char WALL_CIRCLE[] =    "pictures\\circular_wall.png";
//Splash screen
const char SPLASH_SCREEN[] =  "pictures\\splash_screen.png";

//Game over screen
const char GAME_OVER[] =	  "pictures\\game_over.png";

//Menu screen
const char MENU_SCREEN[] =	  "pictures\\game_menu.png";

//Cheat code screen
const char CHEAT_SCREEN[] =	  "pictures\\cheat_codes.png";	

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
enum GameStates {intro, gameMenu, cheatCodes, level_one, level_two, victory, gameover};

#pragma region Level One Setup
const int wallOneX = 0;
const int wallOneY = 100;

const int levelOnePlayerX = 10;
const int levelOnePlayerY = 10;


#pragma endregion Level One Setup

#endif
