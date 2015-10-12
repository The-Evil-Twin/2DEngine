//==================================================================================================
// Codename: 2D Engine
// Basic game Window
// Version 1.0.1
//==================================================================================================
#include <windows.h>
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
// Constants
const char CLASS_NAME[] = "2DEngineWindowClass";
const char APP_TITLE[] = "2DEngine";

//==================================================================================================
// Where the Program Starts
//==================================================================================================
int CALLBACK
WinMain(HINSTANCE Instance,
HINSTANCE PrevInstance,
LPSTR CmdLine,
int ShowCode)
{
	//MessageBox(0, "Hope this works", "Game", MB_OK|MB_ICONINFORMATION);

	// Creates a Mutex to Prevent Multiple Instances of the game
	if (AnotherInstance())
		return false;

	// Creates the Window
	if (!CreateMainWindow(Instance, ShowCode))
		return false;

	// Loops until done
	int done = 0;
	MSG msg;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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
	wcx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = MainWindowProc;
	//wcx.cbCLsExtra = 0;
	//wcx.cbWndExtra = 0;
	wcx.hInstance = Instance;
	wcx.Icon = NULL;
	wcx.lpszClassName = CLASS_NAME; //Global Variable
	wcx.hIconSm = NULL;

	if (RegisterClass(&wcx))
		return false;

	HWND WindowHandle =
		CreateWindowEx(
		0,
		wcx.lpszClassName,
		APP_TITLE, //Global Variable
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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
					OutputDebugStringA("WM_SIZE/n");
	} break;

	case WM_DESTROY:
	{
					   OutputDebugStringA("WM_DESTROY/n");
					   PostQuitMessage(0);
					   return 0;
	} break;

	case WM_CHAR:
		switch (wParam)
		{
		case 0x08:
		case 0x0A:
		case 0x0D:
		case 0x1B:
			MessageBeep((UINT)-1);
			return 0;
		default:
			ch = (TCHAR)wParam;
			InvalidateRect(Window, NULL, TRUE);
			return 0;
		} break;

	case WM_CLOSE:
	{
					 OutputDebugStringA("WM_CLOSE/n");
	} break;

	case WM_ACTIVATEAPP:
	{
						   OutputDebugStringA("WM_ACTIVATEAPP/n");
	} break;

	case WM_PAINT:
	{
					 hdc = BeginPaint(Window, &ps);
					 GetClientRect(Window, &rect);

					 TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);
					 EndPaint(Window, &ps);
					 return 0;
	} break;

	default:
	{
			   Result = DefWindowProc(Window, msg, wParam, lParam);
	} break;
	}

	return(Result);
}

//==================================================================================================
// Used to Check is another instance of the program is running
//==================================================================================================
bool AnotherInstance()
{
	HANDLE ourMutex;
	// Attempt to create a mutex using out unique string
	ourMutex = CreateMutex(NULL. true, "BLDEW0RKZ");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;

	return false;
}