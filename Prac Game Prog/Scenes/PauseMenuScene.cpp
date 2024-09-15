#include "PauseMenuScene.h"

#include "../Systems/Managers/SceneManager.h"
#include "../Systems/Managers/InputManager.h"



PauseMenuScene::PauseMenuScene()
{
    Scene(PAUSE_MENU);
}

// void PauseMenuScene::UpdateScene(int framesToUpdate, float deltaTime)
//
// {
//     //  ypdate stuff
//     
// 	bool isMoving = false;
// 	static bool wasMoving = false; // Track the previous movement state
//
// 	// Update timeSinceLastSound
// 	timeSinceLastSound += deltaTime;
//
// 	//	Acquire the device.
// 	dInputKeyboardDevice->Acquire();
// 	dInputMouseDevice->Acquire();
//
// #pragma region MOUSE_INPUTS
// 	//	MOUSE INPUT EVENT
// 	mousePos.x += mouseState.lX;
// 	mousePos.y += mouseState.lY;
//
// 	if (mouseState.rgbButtons[0] & 0x80) 
// 	{
// 		std::cout << "LEFT CLICK" << std::endl;
// 	}
//
// 	if (mouseState.rgbButtons[1] & 0x80)
// 	{
// 		std::cout << "RIGHT CLICK" << std::endl;
// 	}
//
// #pragma endregion
//
// #pragma region KEYBOARD_INPUTS
// 	//	KEYBOARD INPUT EVENT
// 	if (diKeys[DIK_ESCAPE] & 0x80)
// 	{
// 		
// 	}
//
// 	if (diKeys[DIK_F] & 0x80)
// 	{
// 		//destory sprite brush since it holds d3ddevice
// 		spriteBrush->Release();
// 		spriteBrush = nullptr;
// 		lineInterface->Release();
// 		lineInterface = nullptr;
// 		fontInterface->Release();
// 		fontInterface = nullptr;
// 		//change the Presentation Params for the D3DDevice and then reset it to take effect
// 		if (d3dPP.Windowed) {
// 			//if windowed, set to fullscreen
// 			d3dPP.Windowed = false;
// 		}
// 		else
// 		{
// 			//else, set to windowed
// 			d3dPP.Windowed = true;
// 		}
// 		HRESULT hr = d3dDevice->Reset(&d3dPP);
// 		if (FAILED(hr))
// 		{
// 			std::cout << "Error : " << DXGetErrorString(hr) << "\nDescription : " << DXGetErrorDescription(hr) << '\n';
// 		}
// 	}
//
// #pragma region PLAYER_KEYBOARD_INPUTS
// 	// player inputs
// 	auto e = this->entityManager->GetEntity(PLAYER);
// 	auto t = e->transform;
// 	auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(e->rigidbody);
// 	D3DXVECTOR2 forceApplied = D3DXVECTOR2(0,0);
// 	if (diKeys[DIK_W] & 0x80)
// 	{
// 		forceApplied += D3DXVECTOR2(0,-1);
// 		//forceApplied.x = sin(t->rotation) * thrust;
// 		//forceApplied.y = -cos(t->rotation) * thrust;
// 		
// 		isMoving = true;
//
// 		//Sprite Animation
// 		
// 	}
//
// 	if (diKeys[DIK_S] & 0x80)
// 	{
// 		forceApplied += D3DXVECTOR2(0,1);
// 		isMoving = true;
//
// 		//Sprite Animation
// 	}
//
// 	if (diKeys[DIK_A] & 0x80)
// 	{
// 		//t->rotation -= framesToUpdate * rotationSpeed;
// 		forceApplied += D3DXVECTOR2(-1,0);
// 		isMoving = true;
//
// 		//Sprite Animation
//
// 	}
//
// 	if (diKeys[DIK_D] & 0x80)
// 	{
// 		forceApplied += D3DXVECTOR2(1,0);
// 		isMoving = true;
//
// 		//Sprite Animation
// 		
// 	}
//
// 	D3DXVec2Normalize(&forceApplied,&forceApplied);
// 	rgb->ApplyForce(forceApplied * thrust * framesToUpdate);
//
// 	auto e1 = this->entityManager->GetEntity(ENEMY);
// 	auto t1 = e1->transform;
// 	auto rgb1 = std::dynamic_pointer_cast<Rigidbody2DComponent>(e1->rigidbody);
// 	D3DXVECTOR2 forceApplied1 = D3DXVECTOR2(0,0);
// 	if (diKeys[DIK_UP] & 0x80)
// 	{
// 		forceApplied1 += D3DXVECTOR2(0,-1);
// 		//forceApplied.x = sin(t->rotation) * thrust;
// 		//forceApplied.y = -cos(t->rotation) * thrust;
// 		
// 		isMoving = true;
// 	}
//
// 	if (diKeys[DIK_DOWN] & 0x80)
// 	{
// 		forceApplied1 += D3DXVECTOR2(0,1);
// 		isMoving = true;
// 	}
//
// 	if (diKeys[DIK_LEFT] & 0x80)
// 	{
// 		//t->rotation -= framesToUpdate * rotationSpeed;
// 		forceApplied1 += D3DXVECTOR2(-1,0);
// 		isMoving = true;
// 	}
//
// 	if (diKeys[DIK_RIGHT] & 0x80)
// 	{
// 		forceApplied1 += D3DXVECTOR2(1,0);
// 		isMoving = true;
// 	}
// 	
// 	D3DXVec2Normalize(&forceApplied1,&forceApplied1);
// 	rgb1->ApplyForce(forceApplied1 * thrust * framesToUpdate);
// #pragma endregion
// 	
// #pragma endregion
//
// 	// Sprite Animation Update															
// 	auto sprites = this->componentManager->GetComponents(SPRITE2D_RENDERER);
// 	for (auto component : sprites) {
// 		//std::cout << "Animating" << '\n';
// 		auto sprite2d = std::dynamic_pointer_cast<Sprite2DRendererComponent>(component);
// 		sprite2d->UpdateSpriteAnimation(framesToUpdate);
// 	}
//
// 	// Play sound only when movement starts and regulate it with deltaTime
// 	static float timeSinceLastSound = 0.0f;
// 	timeSinceLastSound += deltaTime;
//
// 	if (isMoving && !wasMoving && timeSinceLastSound >= 0.5f) // 0.5 seconds between sounds
// 	{
// 		audioManager.PlayAudio(audioEntity->audios[0], t->position.x, SCREEN_WIDTH); // pans left and right
// 		timeSinceLastSound = 0.0f; // Reset the timer
// 	}
//
// 	
//     
// }
void PauseMenuScene::ToggleFullscreen()
{
	std::cout << "Fullscreened" << '\n';
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
	HRESULT hr = d3dDevice->Reset(&d3dPP);
	if (FAILED(hr))
	{
		std::cout << "Error : " << DXGetErrorString(hr) << "\nDescription : " << DXGetErrorDescription(hr) << '\n';
	}
}

void PauseMenuScene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> sceneManager)
{
	pauseMenuSceneManager = sceneManager;
	

	// Update timeSinceLastSound
	timeSinceLastSound += deltaTime;

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();

#pragma region MOUSE_INPUTS
	//	MOUSE INPUT EVENT
	mousePos.x += mouseState.lX;
	mousePos.y += mouseState.lY;

	mousePointerEntity->transform->position.x += mouseState.lX;
	mousePointerEntity->transform->position.y += mouseState.lY;

	//ATTACK WHEN RELEASE
	bool currentLeftClickState = (mouseState.rgbButtons[0] & 0x80) != 0;
	if (!currentLeftClickState && attackTriggered)
	{
		// The LEFT CLICK was just released
		std::cout << "LEFT CLICK" << std::endl;
	}
	attackTriggered = currentLeftClickState;

	if (mouseState.rgbButtons[1] & 0x80)
	{
		std::cout << "RIGHT CLICK" << std::endl;
	}

#pragma endregion

#pragma region KEYBOARD_INPUTS
	//	KEYBOARD INPUT EVENT
	if (diKeys[DIK_ESCAPE] & 0x80)
	{
		sceneManager->UnloadScene(false);
		sceneManager->LoadScene(GAME_SCENE);
		return;
	}
#pragma endregion

	// Sprite Animation Update															
	auto sprites = this->componentManager->GetComponents(SPRITE2D_RENDERER);
	for (auto component : sprites) {
		//std::cout << "Animating" << '\n';
		auto sprite2d = std::dynamic_pointer_cast<Sprite2DRendererComponent>(component);
		sprite2d->UpdateSpriteAnimation(framesToUpdate);
	}

	
}

void PauseMenuScene::AddIntoScene()
{
	//	buffers for temporary assignment of data to the components
	std::shared_ptr<Sprite2DRendererComponent> spriteComponent;
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<Rigidbody2DComponent> rigidbodyComponent;
	std::shared_ptr<Polygon2DColliderComponent> polygon2dColliderComponent;
	std::shared_ptr<Audio2DComponent> audioComponent;
	std::shared_ptr<Audio2DComponent> audioBGM;

	//UI stuff
	//Resume Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/resumebutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH / 2, 200);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23)});
	polygon2dColliderComponent->collsionEventScript = std::make_shared<ResumeButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .0f;
	rigidbodyComponent->mass = 1000000.0f;
	rigidbodyComponent->restitution = .7f;
	
	
	//	for testing
	collider2 = polygon2dColliderComponent;
	
	// Options button to options menu
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/optionsbutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH / 2, 300);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	polygon2dColliderComponent->collsionEventScript = std::make_shared<OptionButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->restitution = .4f;


	//Quit button to main menu
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/quitbutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH/2, 400);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	polygon2dColliderComponent->collsionEventScript = std::make_shared<PauseMenuQuitButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;


	// Mouse pointer
	entity = this->entityManager->CreateEntity(MOUSE_POINTER);
	mousePointerEntity = entity;
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/mousePointer.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 16;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 16;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);

	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(mousePos.x, mousePos.y);
	transformComponent->scale = D3DXVECTOR2(1, 1);

	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-1, -1), D3DXVECTOR2(-1, 1), D3DXVECTOR2(1, 1), D3DXVECTOR2(1, -1) });
	//polygon2dColliderComponent->collsionEventScript = std::make_shared<PrintStringEventScript>();
	polygon2dColliderComponent->relativePos = D3DXVECTOR2(0, 0);
	polygon2dColliderComponent->isEventTrigger = true;
	mousePointerCollider = polygon2dColliderComponent;

	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;

}

void PauseMenuScene::InitSceneAudio()
{
}


