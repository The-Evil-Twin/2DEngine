
/* 
 * Graphics class header file
 * Ronald Liu
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifndef _DEBUG
#define D3D_DEBUG_INFO
#endif

#include <d3d9.h>
#include "constants.h"
#include "gameError.h"

//DirectX pointer types
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D 		LPDIRECT3D9

// Color defines
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB) ((((a)&0xff)<<24) | (((r)&0xff)<<16) | (((b)&0xff)<<12) | (((g)&0xff)<<8) | ((b)&0xff)))

class Graphics
{
	private:
		// DirectX pointers
		LP_3D 					direct3d;
		LP_3DDEVICE				device3d;
		D3DPRESENT_PARAMETERS	d3dpp;
		// Variables
		HRESULT		result;
		HWND		hwnd;
		bool		fullscreen;
		int			width;
		int			height;
		// Initializes Direct3d presentation parameters
		// Nothing needs to be done by us
		void initD3Dpp();

	public:
		// Constructor
		Graphics();
		// Destructor
		virtual ~Graphics();
		// Safely frees/releases direct3d and device3d
		void releaseAll();
		/* 
		 * Initializes DirectX graphics
		 * 		hw = Handle to the Window
		 * 		width = Width of the Window
		 * 		height = Height of the Window
		 * 		fscreen = Fullscreen Yes / No
		 * 		Throws GameError if there is a problem
		 */
		void initialize(HWND hw, int width, int height, bool fscreen);

		// Displays the off screen backbuffer to the screen
		HRESULT showBackbuffer();
};
#endif