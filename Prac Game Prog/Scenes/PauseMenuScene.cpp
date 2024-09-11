#include "PauseMenuScene.h"

#include "../Systems/Managers/SceneManager.h"


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

void PauseMenuScene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> scene_manager)
{
    //  ypdate stuff
    
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
		HRESULT hr = d3dDevice->Reset(&d3dPP);
		if (FAILED(hr))
		{
			std::cout << "Error : " << DXGetErrorString(hr) << "\nDescription : " << DXGetErrorDescription(hr) << '\n';
		}
	}

#pragma region PLAYER_KEYBOARD_INPUTS
	// player inputs
	auto e = this->entityManager->GetEntity(PLAYER);
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

	auto e1 = this->entityManager->GetEntity(ENEMY);
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

	//testing
	if (diKeys[DIK_L] & 0x80)
	{
		
		isSwitchScene = true;
	}
	
	D3DXVec2Normalize(&forceApplied1,&forceApplied1);
	rgb1->ApplyForce(forceApplied1 * thrust * framesToUpdate);
#pragma endregion
	
#pragma endregion

	// Sprite Animation Update															
	auto sprites = this->componentManager->GetComponents(SPRITE2D_RENDERER);
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
		audioManager.PlayAudio(audioEntity->audios[0], t->position.x, SCREEN_WIDTH); // pans left and right
		timeSinceLastSound = 0.0f; // Reset the timer
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
	
	// Test audio entity
	audioEntity = this->entityManager->CreateEntity(ENEMY);
	// Sprite component
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(audioEntity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/04.bmp", &spriteInfo1.texture);
	spriteInfo1.sheetHeight = spriteInfo1.spriteHeight = 64;
	spriteInfo1.sheetWidth = spriteInfo1.spriteWidth = 64;
	spriteInfo1.totalRows = 1;
	spriteInfo1.totalCols = 1;
	spriteComponent->InitSpriteInfo(spriteInfo1);

	// Sprite transform
	transformComponent = this->componentManager->CreateTransformComponent(audioEntity);
	transformComponent->position = D3DXVECTOR2(500,500);
	transformComponent->scale = D3DXVECTOR2(1,1);
	transformComponent->rotation = 0.0f;

	// Physics stuff
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(audioEntity);
	rigidbodyComponent->friction = 0.5f;

	// Audio stuff
	// this = current this, call componentManager to create Audio2DComponent, e = parent entity
	audioComponent = this->componentManager->CreateAudio2DComponent(audioEntity);
	audioBGM = this->componentManager->CreateAudio2DComponent(audioEntity);
	audioComponent->LoadSound("Assets/Sounds/right-gravel-footstep-2.wav", false,false);  // [0]
	audioBGM->LoadSound("Assets/Sounds/jazz-loop.mp3", true, false); // [1]
	//au2d->LoadSound("Assets/Sounds/jazz-loop.mp3", false, false);

	//	pls determine freq then set it
	//au2d->setFrequency()

	//MILITIA
	entity = this->entityManager->CreateEntity(PLAYER);

	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
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

	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(1500, 100);
	transformComponent->scale = D3DXVECTOR2(2, 2);

	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->friction = 0.5f;
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-16, -24), D3DXVECTOR2(16, -24), D3DXVECTOR2(16, 24), D3DXVECTOR2(-16, 24)});
	polygon2dColliderComponent->collsionEventScript = std::make_shared<PrintStringEventScript>(); //child class of EventScript btw
	//	for testing
	collider1 = polygon2dColliderComponent;

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
	transformComponent->position = D3DXVECTOR2(200, 200);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23)});
	
	//	for testing
	collider2 = polygon2dColliderComponent;

	//Volume Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/volumebutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 300);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	

	//Fullscreen Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/fullscreenbutton.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 45;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 127;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 400);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	
	// Main Menu buttons
	// adding later
}


