//==================================================================================================
// Codename: Fracture
// Basic game Window
// By Ronald Liu
// Version 1.0.1
//==================================================================================================
#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "graphics.h"
// Prototypes
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT WINAPI MainWindowProc(HWND, UINT, WPARAM, LPARAM);
bool CreateMainWindow(HINSTANCE, int);
bool AnotherInstance();
// Global Variables
HINSTANCE hinst;
HDC hdc;
RECT rect;
PAINTSTRUCT ps;
TCHAR ch = ' ';
// Graphics Pointer
// NEED TO CREATE A GRAPHICS CLASS : Graphics *graphics;
Graphics *graphics;
// Constants
const char CLASS_NAME[] = "FractureWindowClass";
const char APP_TITLE[] = "Fracture";
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = 1280;
const UINT GAME_HEIGHT = 720;

//==================================================================================================
// Where the Program Starts
//==================================================================================================
int WINAPI WinMain( HINSTANCE Instance,
                    HINSTANCE PrevInstance,
                    LPSTR CmdLine,
                    int ShowCode)
{
    // Checks for Memory Leaks
    #if defined(DEBUG) | defined (_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif
    MSG msg;
    // Creates the Window
    if (!CreateMainWindow(Instance, ShowCode))
        return false;

    try {
        graphics = new Graphics;
        graphics -> initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
        int done = 0;
        while (!done)
        {
            if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    done = 1;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }   
        }
        SAFE_DELETE(graphics);
        return msg.wParam;
    } catch (const GameError &err) {
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    } catch (...) {
        MessageBox(NULL, "Unknown Error Occurred in game.", "Error", MB_OK);
    }
    SAFE_DELETE(graphics);
    return msg.wParam;
}


//==================================================================================================
// Used to Create the Window
// Returns false is Error
//==================================================================================================
bool CreateMainWindow(HINSTANCE Instance, int ShowCode)
{
    WNDCLASSEX wcx = {};
    HWND WindowHandle;

    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW|CS_VREDRAW;
    wcx.lpfnWndProc = MainWindowProc;
    // wcx.cbCLsExtra = 0;
    // wcx.cbWndExtra = 0;
    wcx.hInstance = Instance;
    wcx.hIcon = NULL;
    wcx.lpszClassName = CLASS_NAME; //Global Variable
    wcx.hIconSm = NULL;

    if (RegisterClassEx(&wcx) == 0 || AnotherInstance() == true)
        return false;

    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPEDWINDOW

    WindowHandle = CreateWindowEx(
                    0,
                    wcx.lpszClassName,
                    APP_TITLE, //Global Variable
                    style,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    0,
                    0,
                    Instance,
                    0);

    if (!WindowHandle)
        return false;
    if (!FULLSCREEN) 
    {
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        MoveWindow( hwnd, 
                    0, 
                    0, 
                    GAME_WIDTH+(GAME_WIDTH-clientRect.right), 
                    GAME_HEIGHT+(GAME_HEIGHT-clientRect.bottom), 
                    TRUE);
    }
    ShowWindow(WindowHandle, ShowCode);
    UpdateWindow(WindowHandle);
    return true;
}

//==================================================================================================
// Windows event Callback Function
//==================================================================================================
LRESULT WINAPI MainWindowProc(HWND Window,
                                UINT msg,
                                WPARAM wParam,
                                LPARAM lParam)
{
    LRESULT Result = 0;

    switch (msg)
    {
        case WM_SIZE:
        {
            OutputDebugStringA("WM_SIZE\n");
        } break;
        case WM_DESTROY:
        {
            OutputDebugStringA("WM_DESTROY\n");
            PostQuitMessage(0);
            return 0;
        } break;
        case WM_CHAR:
            switch (wParam)
            {
                case ESC_KEY:
                    MessageBeep((UINT) -1);
                    PostQuitMessage(0);
                    return 0;
                default:
                    ch = (TCHAR) wParam;
                    InvalidateRect(Window, NULL, TRUE);
                    return 0;
            } break;
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            OutputDebugStringA("WM_CLOSE\n");
            return 0;
        } break;
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        } break;
        default:
        {
            Result = DefWindowProc(Window, msg, wParam, lParam);
        } break;
    }
    return(Result);
}

// ==================================================================================================
// Used to Check is another instance of the program is running
// ==================================================================================================
bool AnotherInstance()
{
    HANDLE ourMutex;
    // Attempt to create a mutex using out unique string
    ourMutex = CreateMutex(NULL, true, "BLDEW0RKZ");

    if (GetLastError() == ERROR_ALREADY_EXISTS)
        return true;

    return false;
}