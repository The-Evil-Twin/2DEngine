#ifndef _CONSTANTS_H            
#define _CONSTANTS_H            
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char BACKGROUND_IMAGE[]  = "pictures\\sunny.png"; 
const char CHARACTER_IMAGE[]   = "pictures\\WallSocketLady.png";   // CHARACTER
const char GROUND_IMAGE[] = "pictures\\Grass.png";   // GRASS GROUND

// window
const char CLASS_NAME[] = "2DEngine";
const char GAME_TITLE[] = "2DEngine";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
const float GRAVITY = 1000.0f;

// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR CHARACTER_LEFT_KEY    = VK_LEFT;     // left arrow
const UCHAR CHARACTER_RIGHT_KEY   = VK_RIGHT;    // right arrow
const UCHAR CHARACTER_UP_KEY      = VK_UP;       // up arrow
const UCHAR CHARACTER_DOWN_KEY    = VK_DOWN;     // down arrow

#endif
