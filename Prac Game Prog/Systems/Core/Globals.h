//	make sure Multi-byte char set is used and Linker subsystem is set to Not Set

//	At Project Properties -> Configuration Properties -> VC++ Directories, 
//		- Add $(DXSDK_DIR)include\ to Include Directories.
//		- Add $(DXSDK_DIR)lib\x86 to Library Directories

//	At Project Properties -> Configuration Properties -> Linker -> Input, 
//		- Add d3d9.lib to Additional Dependencies
//		- Add d3dx9.lib to Additional Dependencies

#pragma region PREPROCESSOR
//	Ask the compiler to include minimal header files for our program.
//	pre-processor, processed before the rest of the program
#define WIN32_LEAN_AND_MEAN		// make code lean and stong (Bruce Lee)
#include <Windows.h>	//	compile stuff from Windows.h first then compile the rest

//	include direct3d 9
#include <d3d9.h>
//	include the D3DX9 library
#include <d3dx9.h>

//error checking stuff
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

//	include the Direct Input library.
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <iostream>
#include "fmod.hpp"
//	FMOD VC LIB
#pragma comment(lib, "fmod_vc.lib")

//for testing
#include "../../Components/Polygon2DColliderComponent.h"

#pragma endregion

#ifndef GLOBAL_H
#define GLOBAL_H

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

extern int intendedFPS;
//	Window handle
extern HWND g_hWnd;
extern WNDCLASS wndClass;
extern HINSTANCE hInstance;
extern FILE* stream; // for console output

extern IDirect3D9* direct3D9;
//	pointer to virtual gpu
extern IDirect3DDevice9* d3dDevice;
//	define how the screen presents
//	create a box to store my virtual GPU requirements
extern D3DPRESENT_PARAMETERS d3dPP;


//	INPUT STUFF
//	Direct Input object.
extern LPDIRECTINPUT8 dInput;
//	Direct Input devices.
extern LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
extern LPDIRECTINPUTDEVICE8 dInputMouseDevice;
//	Key input buffer
extern BYTE  diKeys[256];
extern DIMOUSESTATE mouseState;
extern D3DXVECTOR3 mousePos;

//	pointer to sprite interface/brush
extern LPD3DXSPRITE spriteBrush;
extern LPD3DXFONT fontInterface;
extern LPD3DXLINE lineInterface;

//extern FrameTimer* gameTimer;

// Audio stuff
extern FMOD::System* audioSystem;	//	virtual sound card
extern FMOD::Channel* channel;	//

//for testing purposes
extern std::shared_ptr<Polygon2DColliderComponent> collider1, collider2;

extern float fullscreenCooldown;
extern float fullscreenTimer;

#endif // GLOBAL_H
    
