//==================================================================================================
// Codename: BladeWorks
// Basic game Window
// Version 1.0.1
//==================================================================================================
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
// Prototypes

//=================================================================================================
// This class is the Object Class, it is where all the information for the objects displayed should
// be stored. 
//=================================================================================================
class NuObject {
public:
	int xPos;
	int yPos;
	int type;
	LPCSTR name;
	int num;
	LPARAM reference;
	//NuObject();

NuObject(HWND, LPCSTR, int, int, int, int, int);

//==================================================================================================
// returns the stored yposition on the gamescreen
//================================================
int getYPos() {
	return yPos;
}
//================================================
// returns the stored xposition on the gamescreen
//================================================
int getXPos() {
	return xPos;
}
//===============================================================================================
// returns the stored type (aka a number to decide what if statement should be valid on creation
//===============================================================================================
int getType() {
	return type;
}
//================================================
// chenges the stored yposition on the gamescreen
//================================================
void ChangeYPos(int newVal) {
	yPos = newVal;
	return;
}
//================================================
// changes the stored xposition on the gamescreen
//================================================
void ChangeXPos(int newVal) {
	xPos = newVal;
	return;
}
//================================================
// change the type, currently not implemented
//================================================
void ChangeType(int newVal) {
	type = newVal;
	return;
}
//================================================
// returns the name, LPCSTR is a type of string
//================================================
LPCSTR getName() {
	return name;
}
//================================================
// changes the name
//================================================
void ChangeName(LPCSTR newName) {
	name = newName;
	return;
}
int getNum() {
	return num;
}
LPARAM getReference() {
	return reference;
}
//NuObject(HWND parent, LPCSTR title, int x, int y);

};
//============================================================
// Define a data type, used to differentiate between 
// Different children being activated within a parent window
// used with the menu portion of creation
//============================================================

#define ID_ADD 1
#define ID_DATA 2
#define ID_CHANGEFILE 4
#define ID_NAME 5
#define ID_XPOS 6
#define ID_YPOS 7
//=====================================================================
// This is the Constructor for the NuObject, called when it is created
//=====================================================================

NuObject::NuObject(HWND parent, LPCSTR title, int typ, int x, int y, int ImX, int ImY) {
	//name = title;
	xPos = ImX;
	yPos = ImY;
	type = typ;
	name = title;
	reference = (LPARAM)CreateWindow(
		TEXT("BUTTON"),                 /* Class Name */
		title,							/* Title */
		WS_VISIBLE | WS_CHILD,          /* Style */
		x, y,							/* Position */
		80, 20,							/* Size */
		parent,							/* Parent */
		(HMENU)ID_DATA,                 /* Menu type */
		NULL,                           /* Instance */
		0);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT WINAPI MainWindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI Game_Window(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI Object_List(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI Object_Details(HWND, UINT, WPARAM, LPARAM);

using namespace std;
bool update = true;


bool CreateMainWindow(HINSTANCE, int);
bool AnotherInstance();
// Global Variables
HINSTANCE hinst;
HDC hdc;
RECT rect;
HWND mainWindow;
PAINTSTRUCT ps;
TCHAR ch = ' ';
HWND g_hwndChildren[4];
// Constants
const char CLASS_NAME[] = "2DEngineWindowClass";
const char CLASS_NAMEZ[] = "Tryit";
const char CLASS_NAM[] = "Again";
const char APP_TITLE[] = "2DEngine";
int arrSize;

HWND NameEditor;
HWND xEditor;
HWND yEditor;
int CurEdit = -1;

//==================================================================================================
// These hold the pieces of information for each created object, the ListNames is a companion to
// List as LPCSTR and string conversion is annoying.
// =================================================================================================
vector <NuObject*> List[1];
vector <string> ListNames[1];

//==================================================================================================
// Create the Methods to overide windowsx.h methods here | Still need to edit the code, currently anothers
//may remove the bottom window, as it currently serves no purpose
//==================================================================================================

void
OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	//Start working on the general layout
	HDWP hdwp = BeginDeferWindowPos(4);
	int cxHalf = cx / 2;
	// Use this to define where the child windows should be drawn.
	if (hdwp) hdwp = DeferWindowPos(hdwp, g_hwndChildren[0],
		NULL, 0, 0, 250, cy,
		SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

	if (hdwp) hdwp = DeferWindowPos(hdwp, g_hwndChildren[2],
		NULL, cx-250, 0, 250, cy,
		SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
	if (hdwp) hdwp = DeferWindowPos(hdwp, g_hwndChildren[3],
		NULL, 250, 0, cx-500, cy,
		SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
	if (hdwp) EndDeferWindowPos(hdwp);
}

BOOL
OnCreate(HWND hwnd, LPCREATESTRUCT lpcs)
{
	//WindCLass for the gameWindow
	WNDCLASSEX game = {};
	game.cbSize = sizeof(game);
	game.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	game.lpfnWndProc = Game_Window;
	game.cbClsExtra = 0;
	game.cbWndExtra = 0;
	game.hInstance = hinst;
	game.hIcon = NULL;
	game.hCursor = LoadCursor(NULL, IDC_ARROW);
	game.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	game.lpszClassName = CLASS_NAME;
	game.hIconSm = NULL;

	if (RegisterClassEx(&game) == 0)
		return false;

	//WindClass for the ObjectList Sidebar
	WNDCLASSEX list = {};
	list.cbSize = sizeof(list);
	list.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	list.lpfnWndProc = Object_List;
	list.cbClsExtra = 0;
	list.cbWndExtra = 0;
	list.hInstance = hinst;
	list.hIcon = NULL;
	list.hCursor = LoadCursor(NULL, IDC_ARROW);
	list.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	list.lpszClassName = CLASS_NAMEZ;
	list.hIconSm = NULL;

	if (RegisterClassEx(&list) == 0)
		return false;

	//WindClass for the ObjectDetails Sidebar
	WNDCLASSEX details = {};
	details.cbSize = sizeof(details);
	details.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	details.lpfnWndProc = Object_Details;
	details.cbClsExtra = 0;
	details.cbWndExtra = 0;
	details.hInstance = hinst;
	details.hIcon = NULL;
	details.hCursor = LoadCursor(NULL, IDC_ARROW);
	details.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	details.lpszClassName = CLASS_NAM;
	details.hIconSm = NULL;
	
	if (RegisterClassEx(&details) == 0)
		return false;
			
			//The game Window
			g_hwndChildren[3] =
				CreateWindow(
					game.lpszClassName,
					NULL,
					WS_VISIBLE | WS_CHILD | WS_BORDER,
					0,
					0,
					0,
					0,
					hwnd,
					NULL,
					hinst,
					0);

			//The details Window
			g_hwndChildren[2] =
				CreateWindow(
					details.lpszClassName,
					NULL,
					WS_VISIBLE | WS_CHILD | WS_BORDER,
					0,
					0,
					0,
					0,
					hwnd,
					NULL,
					hinst,
					0);

			//The list window
			g_hwndChildren[0] =
				CreateWindow(
					list.lpszClassName,
					NULL,
					WS_VISIBLE | WS_CHILD | WS_BORDER,
					0,
					0,
					0,
					0,
					hwnd,
					NULL,
					hinst,
					0);

			for (int i = 0; i < 3; i++) {
				if (!g_hwndChildren[0]) return FALSE;
			}

	return TRUE;
}
//==================================================================================================
// Where the Program Starts
//==================================================================================================
int CALLBACK
WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CmdLine,
	int ShowCode)
{
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
	WNDCLASS mainWindow;
	HWND WindowHandle;
	mainWindow.style = 0;
	mainWindow.lpfnWndProc = MainWindowProc;
	mainWindow.cbClsExtra = 0;
	mainWindow.cbWndExtra = 0;
	mainWindow.hInstance = hinst;
	mainWindow.hIcon = NULL;
	mainWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	mainWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	mainWindow.lpszMenuName = NULL;
	mainWindow.lpszClassName = TEXT("Scratch");

	if (!RegisterClass(&mainWindow)) return FALSE;

	WindowHandle = CreateWindow(
		TEXT("Scratch"),                /* Class Name */
		TEXT("GameMakerv0.0.1"),        /* Title */
		WS_OVERLAPPEDWINDOW,            /* Style */
		200, 200,						/* Position */
		1200, 600,						/* Size */
		NULL,                           /* Parent */
		NULL,                           /* No menu */
		hinst,                          /* Instance */
		0);                             /* No special parameters */

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

		//Overwrite OnCreate and OnSize with the methods defined above
		switch (msg)
		{
		HANDLE_MSG(Window, WM_SIZE, OnSize);
		HANDLE_MSG(Window, WM_CREATE, OnCreate);
		
		case WM_DESTROY:
		{
			OutputDebugStringA("WM_DESTROY\n");
			PostQuitMessage(0);
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
		
		default:
		{
			Result = DefWindowProc(Window, msg, wParam, lParam);
		} break;
		}

		return(Result);
	}

//==================================================================================================
// Windows event Callback Function for the game window (center)
//==================================================================================================
LRESULT WINAPI Game_Window(HWND Window,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	
	LRESULT Result = 0;

	switch (msg)
	{
	
	case WM_DESTROY:
	{
		OutputDebugStringA("WM_DESTROY\n");
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_MOUSEACTIVATE:
	{
		SetFocus(Window);
	}
	case WM_CHAR:
		switch (wParam)
		{
		case 0x08:
		case 0x0A:
		case 0x0D:
		case 0x1B:		//ESC
			MessageBeep((UINT)-1);
			return 0;
		default:
			ch = (TCHAR)wParam;
			InvalidateRect(Window, NULL, TRUE);
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


//===================================================================================
// This needs to be called when the change button is pressed on the Object_Details
// Window
//===================================================================================
void writeToFile() {
	//Write to a new file, and replace the old test.txt file
}

//==========================================
//Updates the NuObject List, from test.txt
//==========================================
void UpdateList(HWND Window) {
	ifstream myfile("test.txt");
	int run = 1;
	string name;
	while (myfile >> name) {
		std::string stemp = std::string(name.begin(), name.end());
		LPCSTR sw = stemp.c_str();
		int type;
		myfile >> type;
		int x;
		myfile >> x;
		int y;
		myfile >> y;
		if (List->size() < run) {
			NuObject *temp = new NuObject(Window, sw, type, 10, run * 20, x, y);
			List->push_back(temp);
			ListNames->push_back(name);
		}
		run++;
	}
	arrSize = run - 1;
	myfile.close();
}

LRESULT WINAPI Object_List(HWND Window,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	LRESULT Result = 0;
	switch (msg)
	{
		
	case WM_CREATE: {
		
		GetClientRect(Window, &rect);
		//Create the Create New Object button (this may be removed)

		CreateWindow(
			TEXT("BUTTON"),					/* Class Name */
			TEXT("Add Object"),             /* Title */
			WS_VISIBLE | WS_CHILD,          /* Style */
			0, rect.bottom,					/* Position */
			80, 20,							/* Size */
			Window,                         /* Parent */
			(HMENU) ID_ADD,                 /* No menu */
			NULL,							/* Instance */
			0);
			//
			UpdateList(Window);
		break;
	}
	case WM_COMMAND: {
		
		if (LOWORD(wParam == ID_ADD)) {
			//writeToFile();
			//call UpdateList
			UpdateList(Window);
			InvalidateRect(Window, NULL, TRUE);
			//MessageBox(Window, "Got Here", "OK", MB_OK);
		}
	case BN_CLICKED: {
		if (LOWORD(wParam == ID_DATA)) {

			//Grab what button was pressed, and set the CurEdit var to it's array position
			for (int i = 0; i < arrSize; i++) {
				if ((LPARAM)lParam == (LPARAM)List->at(i)->getReference()) {
					CurEdit = i;
				}
			}

			SendMessage((HWND)g_hwndChildren[2], BN_CLICKED, (WPARAM)wParam, (LPARAM)lParam);

				
		}
		break;
	}
		break;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(Window, &ps);
		EndPaint(Window, &ps);
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
	case WM_MOUSEACTIVATE:
	{
		SetFocus(Window);
	}
	}

	return(Result);
}

//======================================
// The method to change the vector vars
//======================================

void changeData(int xNew, int yNew) {

	for (int i = 0; i < arrSize; i++) {
		if (i == CurEdit) {
			List->at(i)->ChangeXPos(xNew);
			List->at(i)->ChangeYPos(yNew);
		}
	}
}

//================================
//The method to write to test.txt
//================================

void writeFile() {
	ofstream myfile("test.txt");

	for (int i = 0; i < arrSize; i++) {
		
		myfile << ListNames->at(i) << "\n" << List->at(i)->getType() << " " << List->at(i)->getXPos() << " " << List->at(i)->getYPos() << "\n";
	}

	myfile.close();
}



LRESULT WINAPI Object_Details(HWND Window,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	LRESULT Result = 0;

	switch (msg)
	{
		
	case WM_CREATE: {
		
		GetClientRect(Window, &rect);
		NameEditor = CreateWindow("EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 56, 10, 50, 18, Window, (HMENU)ID_NAME, NULL,  0);
		xEditor = CreateWindow("EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 56, 30, 50, 18, Window, (HMENU)ID_XPOS, NULL, 0);
		yEditor = CreateWindow("EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 56, 50, 50, 18, Window, (HMENU)ID_YPOS, NULL, 0);

		//The button to actually do things
		CreateWindow(
			TEXT("BUTTON"),					/* Class Name */
			TEXT("Change"),					/* Title */
			WS_VISIBLE | WS_CHILD,          /* Style */
			170, 0,							/* Position */
			80, 20,							/* Size */
			Window,                         /* Parent */
			(HMENU)ID_CHANGEFILE,           /* Means it has ID of type CHANGEFILE, so it will use the ID_CHANGEFILE case under BN_CLICKED */
			NULL,                           /* Instance */
			0);
		break;
	}
	case WM_COMMAND: {
		
		case BN_CLICKED: {
			switch (LOWORD(wParam))
			{
				//===============
				// This is what happens if the Object_list member button is pressed
				//===============
				case ID_DATA: {
					//SetWindowText(NameEditor, "Hello");
					
					for (int i = 0; i < arrSize; i++) {	
						//MessageBox(Window, "Got Here", "OK", MB_OK);
						if (List->at(i)->getReference() == lParam) {
							string name = ListNames->at(i);
							std::string stemp = std::string(name.begin(), name.end());
							LPCSTR sw = stemp.c_str();
							
							//int y = List->at(i)->yPos;

							wstring xtemp = to_wstring(List->at(i)->xPos);
							wstring ytemp = to_wstring(List->at(i)->yPos);


							SetWindowText(NameEditor, sw);
							SetWindowTextW(xEditor, xtemp.c_str());
							SetWindowTextW(yEditor, ytemp.c_str());
						}
					}
					break;
				}
				//=======================================================
				// This is what happens if the change button is pressed
				//=======================================================
				case ID_CHANGEFILE: {
					//Grab the data from the input boxes
					char xbuffer[10];
					GetWindowText(xEditor, xbuffer, 10);
					int x = atoi(xbuffer);

					char ybuffer[10];
					GetWindowText(yEditor, ybuffer, 10);
					int y = atoi(ybuffer);

					changeData(x, y);
					writeFile();
					break;
				}
			}
			break;
		}		
		break;
	}

	
	case WM_PAINT:
	{
		hdc = BeginPaint(Window, &ps);
		GetClientRect(Window, &rect);
		
		EndPaint(Window, &ps);
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
	case WM_MOUSEACTIVATE:
	{
		//SetActiveWindow(Window);
		SetFocus(Window);
	}
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
	ourMutex = CreateMutex(NULL, true, "BLDEW0RKZ");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;

	return false;
}



