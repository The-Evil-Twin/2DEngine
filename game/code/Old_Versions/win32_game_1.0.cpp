 /*
     The Game I am going to try and create
 */
#include <windows.h>

LRESULT CALLBACK MainWindowProc(HWND Window,
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
            // Post Quit Message
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
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.left;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            static DWORD Operation = WHITENESS;
            PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
            EndPaint(Window, &Paint);
        } break;

        default:
        {
            Result = DefWindowProc(Window, msg, wParam, lParam);
        } break;
    }

    return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CmdLine,
        int ShowCode)
{
    //MessageBox(0, "Hope this works", "Game", MB_OK|MB_ICONINFORMATION);
    WNDCLASS wcx = {};

    wcx.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wcx.lpfnWndProc = MainWindowProc;
    wcx.hInstance = Instance;
    //wcx.hIcon;
    wcx.lpszClassName = "SharpEdgeWindowClass";

    // Could be if (RegisterClass(&WindowClass) == 0) return false;
    if (RegisterClass(&wcx))
    {
        HWND WindowHandle =
            CreateWindowEx(
                    0,
                    wcx.lpszClassName,
                    "SharpEdge",
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    0,
                    0,
                    Instance,
                    0);

        if (WindowHandle)
        {
            for (;;)
            {
                MSG msg;
                BOOL MessageResult = GetMessage(&msg, 0, 0, 0);
                if (MessageResult > 0)
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            // Error Handling
        }
    }

    return(0);
}
