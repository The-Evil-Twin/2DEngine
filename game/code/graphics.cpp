/* 
 * Graphics class for game
 * Ronald Liu
 */
#include "graphics.h"

// Constructor
Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
}

// Destructor
Graphics::~Graphics()
{
	releaseAll();
}

// Release all
void releaseAll()
{
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

// Initialzes DirectX graphics
// Throws GameError on Error
// Calls functions initD3Dpp() and showBackBuffer
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	initD3Dpp();

	// Create a Direct3D Device
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&device3d);
	if (FAILED(result))
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
}

// Initializes D3D presentation parameters
// Throws game error if failed
void Graphics::initD3Dpp()
{
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth	= width;
		d3dpp.BackBufferHeight	= height;
		if (fullscreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount	= 1;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DESCARD;
		d3dpp.hDeviceWindow		= hwnd;
		d3dpp.Windowed			= (!fullscreen);
		d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
	} catch(...)
	{
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error initializeing D3D presentaion parameters"));
	}
}

// Displays the backbuffer
HRESULT Graphics::showBackBuffer()
{
	result = E_FAIL; // Default to fail, replace on success
	//Clear the backbuffer to lime green
	device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,255,0), 0.0f, 0);
	// Display backbuffer to screen
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}