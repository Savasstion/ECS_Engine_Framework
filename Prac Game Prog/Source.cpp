#include <memory>

#include "Systems/Core/Globals.h"
#include "Systems/Core/WindowProcedure.h"
#include "BaseClasses/Clock.h"
#include "BaseClasses/FrameTimer.h"
#include "BaseClasses/Sprite.h"
#include "Components/Polygon2DColliderComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Sprite2DRendererComponent.h"
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

SceneManager sceneManager;

//GAMEPLAY STUFF // TODO : do it someehere else in the future
float thrust = 3.5f;
float rotationSpeed = .1f;

// Audio
Audio au;
float timeSinceLastSound = 0.0f; // Track time since the last sound was played
const float soundInterval = 0.1f; // Time interval between sounds in seconds


//testing vars
std::shared_ptr<Entity> audioEntity;


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

void Update(int framesToUpdate, float deltaTime)
{
	
	bool isMoving = false;
	static bool wasMoving = false; // Track the previous movement state

	// Update timeSinceLastSound
	timeSinceLastSound += deltaTime;

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();

#pragma region MOUSE_INPUTS
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

#pragma endregion

#pragma region KEYBOARD_INPUTS
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

#pragma region PLAYER_KEYBOARD_INPUTS
	// player inputs
	auto e = sceneManager.currentScene->entityManager->GetEntity(PLAYER);
	auto t = e->transform;
	auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(e->rigidbody);
	D3DXVECTOR2 forceApplied = D3DXVECTOR2(0,0);
	if (diKeys[DIK_W] & 0x80)
	{
		forceApplied += D3DXVECTOR2(0,-1);
		//forceApplied.x = sin(t->rotation) * thrust;
		//forceApplied.y = -cos(t->rotation) * thrust;
		
		isMoving = true;

		//Sprite Animation
		
	}

	if (diKeys[DIK_S] & 0x80)
	{
		forceApplied += D3DXVECTOR2(0,1);
		isMoving = true;

		//Sprite Animation
	}

	if (diKeys[DIK_A] & 0x80)
	{
		//t->rotation -= framesToUpdate * rotationSpeed;
		forceApplied += D3DXVECTOR2(-1,0);
		isMoving = true;

		//Sprite Animation

	}

	if (diKeys[DIK_D] & 0x80)
	{
		forceApplied += D3DXVECTOR2(1,0);
		isMoving = true;

		//Sprite Animation
		
	}

	D3DXVec2Normalize(&forceApplied,&forceApplied);
	rgb->ApplyForce(forceApplied * thrust * framesToUpdate);

	auto e1 = sceneManager.currentScene->entityManager->GetEntity(ENEMY);
	auto t1 = e1->transform;
	auto rgb1 = std::dynamic_pointer_cast<Rigidbody2DComponent>(e1->rigidbody);
	D3DXVECTOR2 forceApplied1 = D3DXVECTOR2(0,0);
	if (diKeys[DIK_UP] & 0x80)
	{
		forceApplied1 += D3DXVECTOR2(0,-1);
		//forceApplied.x = sin(t->rotation) * thrust;
		//forceApplied.y = -cos(t->rotation) * thrust;
		
		isMoving = true;
	}

	if (diKeys[DIK_DOWN] & 0x80)
	{
		forceApplied1 += D3DXVECTOR2(0,1);
		isMoving = true;
	}

	if (diKeys[DIK_LEFT] & 0x80)
	{
		//t->rotation -= framesToUpdate * rotationSpeed;
		forceApplied1 += D3DXVECTOR2(-1,0);
		isMoving = true;
	}

	if (diKeys[DIK_RIGHT] & 0x80)
	{
		forceApplied1 += D3DXVECTOR2(1,0);
		isMoving = true;
	}
	
	D3DXVec2Normalize(&forceApplied1,&forceApplied1);
	rgb1->ApplyForce(forceApplied1 * thrust * framesToUpdate);
#pragma endregion
	
#pragma endregion

	// Sprite Animation Update															
	auto sprites = sceneManager.currentScene->componentManager->GetComponents(SPRITE2D_RENDERER);
	for (auto component : sprites) {
		//std::cout << "Animating" << '\n';
		auto sprite2d = std::dynamic_pointer_cast<Sprite2DRendererComponent>(component);
		sprite2d->UpdateSpriteAnimation(framesToUpdate);
	}

	// Play sound only when movement starts and regulate it with deltaTime
	static float timeSinceLastSound = 0.0f;
	timeSinceLastSound += deltaTime;

	if (isMoving && !wasMoving && timeSinceLastSound >= 0.5f) // 0.5 seconds between sounds
	{
		au.PlaySound(audioEntity->audios[0], t->position.x, SCREEN_WIDTH); // pans left and right
		timeSinceLastSound = 0.0f; // Reset the timer
	}

	
}

#pragma region TESTING_FUNCTIONS
//	TESTING OUT A SCENE MANAGER
Sprite spriteInfo, spriteInfo1; //	TODO: make an sprite asset vector
void AddIntoScene(std::shared_ptr<Scene> scene)
{
	//	buffers for temporary assignment of data to the components
	std::shared_ptr<Sprite2DRendererComponent> spriteComponent;
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<Rigidbody2DComponent> rigidbodyComponent;
	std::shared_ptr<Polygon2DColliderComponent> polygon2dColliderComponent;
	std::shared_ptr<Audio2DComponent> audioComponent;
	std::shared_ptr<Audio2DComponent> audioBGM;

	////	Test Entity 1
	//e = scene->entityManager->CreateEntity(PLAYER);
	//
	//c = scene->componentManager->CreateSprite2DRendererComponent(e);
	//D3DXCreateTextureFromFile(d3dDevice, "Assets/mousePointer.png", &spriteInfo.texture);
	//spriteInfo.sheetHeight = spriteInfo.spriteHeight = 40;
	//spriteInfo.sheetWidth = spriteInfo.spriteWidth = 23;
	//spriteInfo.totalRows = 1;
	//spriteInfo.totalCols = 1;
	//c->InitSpriteInfo(spriteInfo);
	//
	//t = scene->componentManager->CreateTransformComponent(e);
	//t->position = D3DXVECTOR2(500,100);
	//t->scale = D3DXVECTOR2(2,2);

	//rgb = scene->componentManager->CreateRigidbody2DComponent(e);
	//rgb->friction = 0.5f;
	//


	////	Test Entity 2
	//e = scene->entityManager->CreateEntity(ENEMY);
	//
	//c = scene->componentManager->CreateSprite2DRendererComponent(e);
	//D3DXCreateTextureFromFile(d3dDevice, "Assets/04.bmp", &spriteInfo1.texture);
	//spriteInfo1.sheetHeight = spriteInfo1.spriteHeight = 64;
	//spriteInfo1.sheetWidth = spriteInfo1.spriteWidth = 64;
	//spriteInfo1.totalRows = 1;
	//spriteInfo1.totalCols = 1;
	//c->InitSpriteInfo(spriteInfo1);
	//
	//t = scene->componentManager->CreateTransformComponent(e);
	//t->position = D3DXVECTOR2(500,500);
	//t->scale = D3DXVECTOR2(1,1);
	//t->rotation = 1;

	//rgb = scene->componentManager->CreateRigidbody2DComponent(e);
	//rgb->friction = 0.5f;

	// Test audio entity
	audioEntity = scene->entityManager->CreateEntity(ENEMY);
	// Sprite component
	spriteComponent = scene->componentManager->CreateSprite2DRendererComponent(audioEntity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/04.bmp", &spriteInfo1.texture);
	spriteInfo1.sheetHeight = spriteInfo1.spriteHeight = 64;
	spriteInfo1.sheetWidth = spriteInfo1.spriteWidth = 64;
	spriteInfo1.totalRows = 1;
	spriteInfo1.totalCols = 1;
	spriteComponent->InitSpriteInfo(spriteInfo1);

	// Sprite transform
	transformComponent = scene->componentManager->CreateTransformComponent(audioEntity);
	transformComponent->position = D3DXVECTOR2(500,500);
	transformComponent->scale = D3DXVECTOR2(1,1);
	transformComponent->rotation = 0.0f;

	// Physics stuff
	rigidbodyComponent = scene->componentManager->CreateRigidbody2DComponent(audioEntity);
	rigidbodyComponent->friction = 0.5f;

	// Audio stuff
	// scene = current scene, call componentManager to create Audio2DComponent, e = parent entity
	audioComponent = scene->componentManager->CreateAudio2DComponent(audioEntity);
	audioBGM = scene->componentManager->CreateAudio2DComponent(audioEntity);
	audioComponent->LoadSound("Assets/Sounds/right-gravel-footstep-2.wav", false,false);  // [0]
	audioBGM->LoadSound("Assets/Sounds/jazz-loop.mp3", true, false); // [1]
	//au2d->LoadSound("Assets/Sounds/jazz-loop.mp3", false, false);

	//	pls determine freq then set it
	//au2d->setFrequency()

	//MILITIA
	entity = scene->entityManager->CreateEntity(PLAYER);

	spriteComponent = scene->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/militia.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 48;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 32;
	spriteInfo.totalRows = 4;
	spriteInfo.totalCols = 4;
	spriteInfo.isAnimated = true;
	spriteInfo1.isDirectional = true;
	spriteInfo.upDirectionValue = 3;
	spriteInfo.leftDirectionValue = 1;
	spriteInfo.rightDirectionValue = 2;
	spriteInfo.downDirectionValue = 0;
	spriteComponent->InitSpriteInfo(spriteInfo);

	transformComponent = scene->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(500, 100);
	transformComponent->scale = D3DXVECTOR2(2, 2);

	rigidbodyComponent = scene->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->friction = 0.5f;
	polygon2dColliderComponent = scene->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-16, -24), D3DXVECTOR2(16, -24), D3DXVECTOR2(16, 24), D3DXVECTOR2(-16, 24)});
	//	for testing
	collider1 = polygon2dColliderComponent;

	//UI stuff
	//Resume Button
	entity = scene->entityManager->CreateEntity(UI);
	spriteComponent = scene->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/resumebutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = scene->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 200);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = scene->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23)});
	//	for testing
	collider2 = polygon2dColliderComponent;

	//Volume Button
	entity = scene->entityManager->CreateEntity(UI);
	spriteComponent = scene->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/volumebutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = scene->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 300);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = scene->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	

	//Fullscreen Button
	entity = scene->entityManager->CreateEntity(UI);
	spriteComponent = scene->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/fullscreenbutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = scene->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 400);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = scene->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	
	// Main Menu buttons
	// adding later
}
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
	LoadInitialTextures();
	CreateDirectInput();
	au.InitAudio();
	

	FrameTimer* gameTimer = new FrameTimer();
	gameTimer->Init(60);
	//	may change how to do this in the future
	AddIntoScene(sceneManager.currentScene);

	// Play background music in loop
	au.PlaySound(audioEntity->audios[1], 0, 0);
	
	while (GameIsRunning()) //game loop i guess
	{
		//	Run all systems
		sceneManager.currentScene->entityManager->UpdateEntityList();
		sceneManager.currentScene->componentManager->UpdateComponentList();
		int framesToUpdate = gameTimer->GetFramesToUpdate();
		float deltaTime = gameTimer->GetDeltaTime();
		//TODO: DO ANIM, PHYSICS COMPONENTS 
		
		//get input
		GetInput();
		//do physics
		//DoPhysics();
		Physics::DoScenePhysics(sceneManager.currentScene, framesToUpdate);
		//AI
		//game update/logic
		Update(framesToUpdate, deltaTime);
		//Draw!!!!
		Graphics::RenderScene(sceneManager.currentScene);
		//play sound
		au.UpdateSound();


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
