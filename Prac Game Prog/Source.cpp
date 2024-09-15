#include <memory>

#include "Systems/Core/Globals.h"
#include "Systems/Core/WindowProcedure.h"
#include "BaseClasses/Clock.h"
#include "BaseClasses/FrameTimer.h"
#include "BaseClasses/Sprite.h"
#include "Components/Polygon2DColliderComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Sprite2DRendererComponent.h"
#include "Scripts/EventScripts/PrintStringEventScript.h"
#include "Systems/Managers/EntityManager.h"
#include "Systems/Core/Graphics.h"
#include "Systems/Core/Physics.h"
#include "Systems/Managers/SceneManager.h"
#include "Systems/Core/Audio.h"


#pragma region GLOBAL_VAR
HRESULT hr;
MSG msg;

// pointer to texture in the gpu vram
//TODO : remove this and place in Scene Manager assets 
LPDIRECT3DTEXTURE9 bg1Texture = nullptr;
LPDIRECT3DTEXTURE9 bg2Texture = nullptr;
LPDIRECT3DTEXTURE9 currentBGTexture = nullptr;
LPDIRECT3DTEXTURE9 mousePointerTexture = nullptr;
LPDIRECT3DTEXTURE9 windowsChinaTexture = nullptr;
LPDIRECT3DTEXTURE9 numbersTexture = nullptr;

//Define a rectange for the sprite for this case/demo
//TODO: mave mouse pointer an entity and remove this 
RECT spriteRect;
RECT textRect;

std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();

//testing vars



#pragma endregion


bool GameIsRunning()
{

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/

	if (msg.message != WM_QUIT)
	{
		/*
				The if- version process one message per one iteration loop
				The while- version will clear the message queue before dealing with your own code.

				Another function is GetMessage.
				This function is not suitable for game, because it will block your program until it recieves a message.
				your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
				Suitable for event based program, such as bussiness app.
			*/
			//	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))	//peek and ask OS : "Ada message ah?"
		{
			//	Receive a quit message
			if (msg.message == WM_QUIT)
				return false;

			//	Translate the message 
			TranslateMessage(&msg);
			//	Send message to your window procedure
			DispatchMessage(&msg);

		}



	}
		return true;
}

#pragma region CLEAN_UP_FUNCTIONS

void CLeanupLoadedTextures()
{
	//	TODO: softcode it in the future
	bg1Texture->Release();
	bg1Texture = nullptr;
	bg2Texture->Release();
	bg2Texture = nullptr;
	currentBGTexture->Release();
	currentBGTexture = nullptr;
	std::cout << "All textures cleared" << '\n';	
}

#pragma endregion

void LoadInitialTextures() 
{
	//TODO: do this in sceneManager 
	//	INIT background texture for the first time
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/bg1.png", &bg1Texture);
	currentBGTexture = bg1Texture;

	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/bg2.png", &bg2Texture);

	//	INIT mouse pointer texture for the first time
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/mousePointer.png", &mousePointerTexture);

	//hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/04.bmp", &windowsChinaTexture);
	hr = D3DXCreateTextureFromFileEx(d3dDevice, "Assets/04.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
										D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
										D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 64), 
										nullptr, nullptr, &windowsChinaTexture);

	hr = D3DXCreateTextureFromFileEx(d3dDevice, "Assets/numbers.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 0),
		nullptr, nullptr, &numbersTexture);
	// numberSpriteRect.top = 0;
	// numberSpriteRect.bottom = numberSpriteRect.top + 32;
	// numberSpriteRect.left = 0;
	// numberSpriteRect.right = numberSpriteRect.left + 32;
	// numberPos.x = 100;
	// numberPos.y = 100;
	// numberPos.z = 0;

}

void CreateConsole()
{
	//	for console for debugging
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "w", stdout);
	
}

void CreateDirectInput() 
{
	//	Create the Direct Input object.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);


	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	//	Create the mouse device.
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//	initialize mousePos at the center
	mousePos.x = SCREEN_WIDTH / 2;
	mousePos.y = SCREEN_HEIGHT / 2;
}

void GetInput() 
{
	
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
	/*---
		For buffered data
			//	Get buffered keyboard data.
			//DWORD items = DEVICE_BUFFER_SIZE;
			//dInputKeyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), deviceBuffer, &items, 0);
			//
			//for(DWORD i=0; i<items; i++)
			//{
			//	if ((deviceBuffer[i].dwData & 0x80) != 0)
			//	{
			//		if (deviceBuffer[i].dwOfs == DIK_UP)
			//		{
			//			std::cout << "UP" << std::endl;
			//		}
			//	}
			//}
	--*/

	
}


#pragma region TESTING_FUNCTIONS
//	TESTING OUT A SCENE MANAGER


#pragma endregion
//	use int main if you want to have a console to print out message
//int main() 


//	use WinMain if you don't want the console
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//INIT
	hInstance = hInst;
	CreateConsole();
	//	ensure window is created successfully then make D3D9 device
	Graphics::SpawnWindow();
	Graphics::CreateD3DDevice();
	//LoadInitialTextures();
	CreateDirectInput();
	audioManager.InitAudio();
	

	FrameTimer* gameTimer = new FrameTimer();
	gameTimer->Init(60);

	sceneManager->LoadScene(GAME_SCENE);

	// Play background music in loop
	
	while (GameIsRunning()) //game loop i guess
	{
		//	Run all systems
		sceneManager->currentScene->entityManager->UpdateEntityList();
		sceneManager->currentScene->componentManager->UpdateComponentList();
		int framesToUpdate = gameTimer->GetFramesToUpdate();
		float deltaTime = gameTimer->GetDeltaTime();
		//TODO: DO ANIM, PHYSICS COMPONENTS 
		
		//get input
		GetInput();
		//do physics
		//DoPhysics();
		Physics::DoScenePhysics(sceneManager->currentScene, framesToUpdate);
		//AI
		//game update/logic
		//remove sceneManager param soon maybe, for now it is a testing var
		sceneManager->currentScene->UpdateScene(framesToUpdate, deltaTime, sceneManager);
		//Draw!!!!
		Graphics::RenderScene(sceneManager->currentScene);
		//play sound
		audioManager.UpdateSound();


		if(sceneManager->currentScene->isSwitchScene)
		{
			SceneEnum num;
			static bool flip = true;
			if(flip)
				num = MAIN_MENU;
			else
			{
				num = GAME_SCENE;
			}
			flip = !flip;
			sceneManager->currentScene->isSwitchScene = false;
			sceneManager->currentScene->SwitchScene(sceneManager, num);
		}
	}

	std::cout << "Starting Clean up" << '\n';
	Graphics::CleanupDirectXInterfaces();
	//CLeanupLoadedTextures();
	Graphics::CleanupD3DDevice();
	Graphics::CleanupWindow();

	std::cout << "Shutting down" << '\n';
	return 0;
}
