//==================================================================================================
// Test
// Version 1.0.1
//==================================================================================================
#include <windows.h>
#include <xaudio2.h>
#include "wave.h"

// Prototypes
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT WINAPI MainWindowProc(HWND, UINT, WPARAM, LPARAM);
bool CreateMainWindow(HINSTANCE, int);
bool AnotherInstance();
// Global Variables
HINSTANCE hinst;
HDC hdc;
//helper class to load wave files; trust me, this makes it MUCH easier
Wave buffer;
RECT rect;
PAINTSTRUCT ps;
TCHAR ch = ' ';
// Constants
const char CLASS_NAME[] = "2DEngineWindowClass";
const char APP_TITLE[] = "2DEngine";
const int NUM_VOICES = 2;
IXAudio2* g_engine;
IXAudio2SourceVoice* g_source[NUM_VOICES];
IXAudio2MasteringVoice* g_master;

//==================================================================================================
// Where the Program Starts
//==================================================================================================
int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CmdLine,
        int ShowCode)
{
    // MessageBox(0, "Hope this works", "Game", MB_OK|MB_ICONINFORMATION);

    // Creates a Mutex to Prevent Multiple Instances of the game
    if (AnotherInstance())
        return false;

	// Initialize the audio engine

	//must call this for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}

	//load a wave file
	if (!buffer.load("click_x.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	//create the source voices, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source[0], buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}

	if (!buffer.load("NoMoreMagic.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -5;
	}

	if (FAILED(g_engine->CreateSourceVoice(&g_source[1], buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -6;
	}

    // Creates the Window
    if (!CreateMainWindow(Instance, ShowCode))
        return false;

    // Loops until done
    int done = 0;
    MSG msg;
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

	g_engine->Release();
	CoUninitialize();
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
    wcx.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wcx.lpfnWndProc = MainWindowProc;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = Instance;
    wcx.hIcon = NULL;
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcx.lpszClassName = CLASS_NAME; //Global Variable
    wcx.hIconSm = NULL;

    if (RegisterClassEx(&wcx) == 0)
        return false;

    WindowHandle =
            CreateWindowEx(
                    0,
                    wcx.lpszClassName,
                    APP_TITLE, //Global Variable
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE,
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

    ShowWindow(WindowHandle, ShowCode);

    UpdateWindow(WindowHandle);
    return true;
}

//==================================================================================================
// Windows event Callback Function
//==================================================================================================
LRESULT WINAPI MainWindowProc (	HWND Window,
                              	UINT msg,
                              	WPARAM wParam,
                              	LPARAM lParam )
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
                case 0x08:
                case 0x0A:
                case 0x0D:
                case 0x1B:		//ESC
                    MessageBeep((UINT) -1);
                    return 0;
                default:
                    ch = (TCHAR) wParam;
					g_source[1]->Start();
					g_source[1]->SubmitSourceBuffer( buffer.xaBuffer() );
                    InvalidateRect(Window, NULL, TRUE);
                    return 0;
            } break;

        case WM_CLOSE: // The "X" At the Upper Right hand corner is clicked
        {
            OutputDebugStringA("WM_CLOSE\n");
            PostQuitMessage(0);
            return 0;
        } break;

        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        } break;
        case WM_PAINT:
        {
            hdc = BeginPaint(Window, &ps);
            GetClientRect(Window, &rect);

            TextOut(hdc, rect.right/2, rect.bottom/2, &ch, 1);
            EndPaint(Window, &ps);
            return 0;
        } break;

        default:
        {
            Result = DefWindowProc(Window, msg, wParam, lParam);
        } break;
    }
	
	//g_source[i]->SubmitSourceBuffer( buffer.xaBuffer() );
	//g_source[i]->Start();

    return(Result);
}

//==================================================================================================
// Used to Check is another instance of the program is running
//==================================================================================================
bool AnotherInstance()
{
    HANDLE ourMutex;
    // Attempt to create a mutex using out unique string
    ourMutex = CreateMutex(NULL, true, "BLDEW0RKZ");

    if (GetLastError() == ERROR_ALREADY_EXISTS)
        return true;

    return false;
}