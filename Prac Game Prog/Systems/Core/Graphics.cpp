#include "Graphics.h"
#include "Globals.h"

MSG Graphics::msg = {};

Graphics::Graphics()
{
    ZeroMemory(&msg,sizeof(msg));
}

bool Graphics::SpawnWindow()
{
    /*
        Step 1
        Define and Register a Window.
    */

    //	Window's structure

    //	Set all members in wndClass to 0.
    ZeroMemory(&wndClass, sizeof(wndClass));
	
    //	These are the fundamental structure members to be specify, in order to create your window.
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hInstance = hInstance;	//	GetModuleHandle(nullptr);
    wndClass.lpfnWndProc = WindowProcedure;
    wndClass.lpszClassName = "Game Class Name insert here";
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    //	Register the window.
    RegisterClass(&wndClass);

    /*
        Step 2
        Create the Window.
    */
    //	You are to refer to MSDN for each of the parameters details.
    g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Valorant 1.6", WS_OVERLAPPEDWINDOW /*WS_EX_TOPMOST | WS_POPUP*/, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(g_hWnd, 1);
	
    //	ShowCursor(false);


    //make sure msg is zeroes
    ZeroMemory(&msg, sizeof(msg));

    return true;

}

void Graphics::CleanupWindow()
{
    //	Free up the memory.
    UnregisterClass(wndClass.lpszClassName, hInstance);
    std::cout << "Unregistering window class" << '\n';
}

void Graphics::CleanupD3DDevice()
{
    if(d3dDevice != nullptr)
    {
        //	Release the device when exiting.
        d3dDevice->Release();
        //	Reset pointer to NULL, a good practice.
        d3dDevice = nullptr;
        std::cout << "D3DDevice cleared" << '\n';
    }
}

void Graphics::CleanupDirectXInterfaces()
{
    //	clean up sprites and textures
    if(spriteBrush != nullptr)
    {
        spriteBrush->Release();
        spriteBrush = nullptr;
        std::cout << "Sprite brush cleared" << '\n';
    }
	
    if (fontInterface != nullptr) 
    {
        fontInterface->Release();
        fontInterface = nullptr;
    }

}

void Graphics::CleanupLoadedTextures()
{
    //  TODO:Softcode clearing all loaded textures using the sceneManager
}

bool Graphics::CreateD3DDevice()
{
    //	define direct3d9
    //	this is where we take the direct3d class and instantiate an obj
    //	becuz method we need is in the class
    direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);


    ZeroMemory(&d3dPP, sizeof(d3dPP));

    //	Refer to Direct3D 9 documentation for the meaning of the members.
    //	requirements for virtual gpu
    d3dPP.Windowed = true;
    d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dPP.BackBufferCount = 1;
    d3dPP.BackBufferWidth = SCREEN_WIDTH;
    d3dPP.BackBufferHeight = SCREEN_HEIGHT;
    d3dPP.hDeviceWindow = g_hWnd;


    //	Create a Direct3D 9 device (virtual gpu).			
    //	change to D3DDEVTYPE_REF if u want a software renderer instead
    HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);



    //if failed, print error message to console
    if (FAILED(hr))
    {
        std::cout << "D3DDevice failed to be created!";
        return false;
    }

    return true;

}

void Graphics::DrawInterfaces()
{
}

int Graphics::Render()
{
    //	Clear the back buffer.
    d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    //	Begin the scene - UNLOCK MEMORY FOR DRAWING
    d3dDevice->BeginScene();

    DrawInterfaces();

    //	End the scene - LOCK THE MEMORY
    d3dDevice->EndScene();

    //	Present the back buffer to screen
    d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
    return 0;
}
