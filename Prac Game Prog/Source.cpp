#include <memory>

#include "Systems/Core/Globals.h"
#include "Systems/Core/WindowProcedure.h"
#include "BaseClasses/Clock.h"
#include "BaseClasses/FrameTimer.h"
#include "BaseClasses/Sprite.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Sprite2DRendererComponent.h"
#include "Systems/Managers/EntityManager.h"
#include "Systems/Core/Graphics.h"
#include "Systems/Managers/SceneManager.h"


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



SceneManager sceneManager;

//GAMEPLAY STUFF // TODO : do it someehere else in the future
float thrust = 3.5f;
float rotationSpeed = .1f;


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

// void CleanupWindow()
// {
// 	//	Free up the memory.
// 	UnregisterClass(wndClass.lpszClassName, hInstance);
// 	std::cout << "Unregistering window class" << '\n';
// }
// void CleanupD3DDevice()
// {
// 	if(d3dDevice != nullptr)
// 	{
// 		//	Release the device when exiting.
// 		d3dDevice->Release();
// 		//	Reset pointer to NULL, a good practice.
// 		d3dDevice = nullptr;
// 		std::cout << "D3DDevice cleared" << '\n';
// 	}
// }
// void CleanupDirectXInterfaces() 
// {
// 	//	clean up sprites and textures
// 	if(spriteBrush != nullptr)
// 	{
// 		spriteBrush->Release();
// 		spriteBrush = nullptr;
// 		std::cout << "Sprite brush cleared" << '\n';
// 	}
// 	
// 	if (fontInterface != nullptr) 
// 	{
// 		fontInterface->Release();
// 		fontInterface = nullptr;
// 	}
//
//
// }

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

bool CreateD3DDevice()
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
	hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);



	//if failed, print error message to console
	if (FAILED(hr))
	{
		std::cout << "D3DDevice failed to be created!";
		return false;
	}

	return true;

}

void DrawInterfaces()
{
	//	make sprite brush
	if(spriteBrush == nullptr)
	{
		hr = D3DXCreateSprite(d3dDevice, &spriteBrush);
		std::cout << "Sprite brush created" << '\n';
	}
	//	check if succeed or fail using hr
	if FAILED(hr)
	{
		std::cout << "spriteBrush fucked\n";
		std::cout << "Error : "<< DXGetErrorString(hr) << "\nDescription : " << DXGetErrorDescription(hr) << '\n';
	}

	//	Create font interface
	if(fontInterface == nullptr)
		hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
			DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Arial", &fontInterface);
	
	//	Create line interface
	if (lineInterface == nullptr)
		hr = D3DXCreateLine(d3dDevice, &lineInterface);
	

	spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	//TODO:put this in a System  
	//	DRAW ALL SPRITE2D Components
	//	Sprite2DRenderer.DrawAllSprites
	for(std::shared_ptr<Component> r : sceneManager.currentScene->componentManager->GetComponents(SPRITE2D_RENDERER))
	{
		std::shared_ptr<Sprite2DRendererComponent> c = std::dynamic_pointer_cast<Sprite2DRendererComponent>(r);
		D3DXMATRIX mat = c->parent->GetTransformMatrix();
		spriteBrush->SetTransform(&mat);
		spriteBrush->Draw(c->spriteInfo.texture,&c->spriteRect,NULL,NULL,D3DCOLOR_XRGB(255, 255, 255));
		
	}
	
	//	note : if u put line::Begin() must end immediately after use cuz it will mess with spriteBrush somehow
	lineInterface->Begin();
	lineInterface->End();

	//	Draw Mouse Pointer
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 23;
	spriteRect.bottom = 40;
	//spriteBrush->Draw(mousePointerTexture, &spriteRect, nullptr, &mousePos, D3DCOLOR_XRGB(255, 255, 255));
	
	spriteBrush->End();

}

int Render()
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

void Update(int framesToUpdate) 
{
	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();

	//	MOUSE INPUT EVENT
	mousePos.x += mouseState.lX;
	mousePos.y += mouseState.lY;

	if (mouseState.rgbButtons[0] & 0x80) 
	{
		std::cout << "LEFT CLICK" << std::endl;
	}

	if (mouseState.rgbButtons[1] & 0x80)
	{
		std::cout << "RIGHT CLICK" << std::endl;
	}

	//	KEYBOARD INPUT EVENT
	if (diKeys[DIK_ESCAPE] & 0x80)
	{
		
	}

	if (diKeys[DIK_F] & 0x80)
	{
		//destory sprite brush since it holds d3ddevice
		spriteBrush->Release();
		spriteBrush = nullptr;
		lineInterface->Release();
		lineInterface = nullptr;
		fontInterface->Release();
		fontInterface = nullptr;
		//change the Presentation Params for the D3DDevice and then reset it to take effect
		if (d3dPP.Windowed) {
			//if windowed, set to fullscreen
			d3dPP.Windowed = false;
		}
		else
		{
			//else, set to windowed
			d3dPP.Windowed = true;
		}
		hr = d3dDevice->Reset(&d3dPP);
		if (FAILED(hr))
		{
			std::cout << "Error : " << DXGetErrorString(hr) << "\nDescription : " << DXGetErrorDescription(hr) << '\n';
		}
	}

	// player inputs
	auto e = sceneManager.currentScene->entityManager->GetEntity(PLAYER);
	auto t = e->transform;
	auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(e->rigidbody);
	
	
	if (diKeys[DIK_W] & 0x80)
	{
		D3DXVECTOR2 forceApplied;
		forceApplied.x = sin(t->rotation) * thrust;
		forceApplied.y = -cos(t->rotation) * thrust;
		rgb->ApplyForce(forceApplied);
	}

	if (diKeys[DIK_S] & 0x80)
	{
		
	}

	if (diKeys[DIK_A] & 0x80)
	{
		t->rotation -= framesToUpdate * rotationSpeed;
	}

	if (diKeys[DIK_D] & 0x80)
	{
		t->rotation += framesToUpdate * rotationSpeed;
	}

	auto e1 = sceneManager.currentScene->entityManager->GetEntity(ENEMY);
	auto t1 = e1->transform;
	auto rgb1 = std::dynamic_pointer_cast<Rigidbody2DComponent>(e1->rigidbody);
	
	if (diKeys[DIK_UP] & 0x80)
	{
		D3DXVECTOR2 forceApplied;
		forceApplied.x = sin(t1->rotation) * thrust;
		forceApplied.y = -cos(t1->rotation) * thrust;
		rgb1->ApplyForce(forceApplied);
	}

	if (diKeys[DIK_DOWN] & 0x80)
	{
		
	}

	if (diKeys[DIK_LEFT] & 0x80)
	{
		t1->rotation -= framesToUpdate * rotationSpeed;
	}

	if (diKeys[DIK_RIGHT] & 0x80)
	{
		t1->rotation += framesToUpdate * rotationSpeed;
	}
	
	//myClock->UpdateClockTime();
}

#pragma region TESTING_FUNCTIONS
//	TESTING OUT A SCENE MANAGER
Sprite spriteInfo, spriteInfo1; //	TODO: make an sprite asset vector
void AddIntoScene(std::shared_ptr<Scene> scene)
{
	
	std::shared_ptr<Sprite2DRendererComponent> c;
	std::shared_ptr<TransformComponent> t;
	std::shared_ptr<Entity> e;
	std::shared_ptr<Rigidbody2DComponent> rgb;

	//	Test Entity 1
	e = scene->entityManager->CreateEntity(PLAYER);
	
	c = scene->componentManager->CreateSprite2DRendererComponent(e);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/mousePointer.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 40;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 23;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	c->InitSpriteInfo(spriteInfo);
	
	t = scene->componentManager->CreateTransformComponent(e);
	t->position = D3DXVECTOR2(500,100);
	t->scale = D3DXVECTOR2(2,2);

	rgb = scene->componentManager->CreateRigidbody2DComponent(e);
	
	//	Test Entity 2
	e = scene->entityManager->CreateEntity(ENEMY);
	
	c = scene->componentManager->CreateSprite2DRendererComponent(e);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/04.bmp", &spriteInfo1.texture);
	spriteInfo1.sheetHeight = spriteInfo1.spriteHeight = 64;
	spriteInfo1.sheetWidth = spriteInfo1.spriteWidth = 64;
	spriteInfo1.totalRows = 1;
	spriteInfo1.totalCols = 1;
	c->InitSpriteInfo(spriteInfo1);
	
	t = scene->componentManager->CreateTransformComponent(e);
	t->position = D3DXVECTOR2(500,500);
	t->scale = D3DXVECTOR2(1,1);

	rgb = scene->componentManager->CreateRigidbody2DComponent(e);
	
}
#pragma endregion

void DoPhysics()
{
	for (auto c : sceneManager.currentScene->componentManager->GetComponents(RIGIDBODY2D))
	{
		auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(c);
		rgb->DoCycleOfMotion();
	}
}

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
	LoadInitialTextures();
	CreateDirectInput();

	FrameTimer* gameTimer = new FrameTimer();
	gameTimer->Init(60);
	//	may change how to do this in the future
	AddIntoScene(sceneManager.currentScene);
	
	while (GameIsRunning()) //game loop i guess
	{
		//	Run all systems
		sceneManager.currentScene->entityManager->Update();
		sceneManager.currentScene->componentManager->Update();
		//TODO: DO ANIM, PHYSICS COMPONENTS 
		
		//get input
		GetInput();
		//do physics
		DoPhysics();
		//AI
		//game update/logic
		Update(gameTimer->GetFramesToUpdate());
		//Draw!!!!
		Render();
		//play sound


		//	Print RGB value of screen on console
		//std::cout << "R = " << R << ", G = " << G << ", B = " << B << '\n';
	}

	std::cout << "Starting Clean up" << '\n';
	Graphics::CleanupDirectXInterfaces();
	CLeanupLoadedTextures();
	Graphics::CleanupD3DDevice();
	Graphics::CleanupWindow();

	std::cout << "Shutting down" << '\n';
	return 0;
}
