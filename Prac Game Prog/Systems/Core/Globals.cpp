#include "Globals.h"

int intendedFPS = 60;

int trashScore = 0;

HWND g_hWnd = nullptr;
HINSTANCE hInstance = GetModuleHandle(nullptr);
WNDCLASS wndClass = WNDCLASS();
FILE* stream = nullptr;
IDirect3D9* direct3D9 = nullptr;
IDirect3DDevice9* d3dDevice = nullptr;
D3DPRESENT_PARAMETERS d3dPP;

LPDIRECTINPUT8 dInput = nullptr;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice = nullptr;
LPDIRECTINPUTDEVICE8 dInputMouseDevice = nullptr;
BYTE diKeys[256];
DIMOUSESTATE mouseState;
D3DXVECTOR3 mousePos = D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0);

LPD3DXSPRITE spriteBrush = nullptr;
LPD3DXFONT fontInterface = nullptr;
LPD3DXLINE lineInterface = nullptr;

FMOD::System* audioSystem;	//	virtual sound card
FMOD::Channel* channel = 0;

std::shared_ptr<Polygon2DColliderComponent> collider1 = nullptr;
std::shared_ptr<Polygon2DColliderComponent> collider2 = nullptr;