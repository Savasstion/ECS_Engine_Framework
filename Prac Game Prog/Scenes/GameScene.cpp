#include "GameScene.h"

#include "../Systems/Managers/SceneManager.h"
#include "../Systems/Managers/InputManager.h"


GameScene::GameScene()
{
    Scene(GAME_SCENE);
}

void GameScene::createTrashEntity(const D3DXVECTOR2& position, const std::string& texturePath, const float size) {
	std::shared_ptr<Sprite2DRendererComponent> spriteComponent;
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<Polygon2DColliderComponent> polygon2dColliderComponent;
	std::shared_ptr<Rigidbody2DComponent> rigidbodyComponent;
	std::shared_ptr<Entity> entity;

	// Create the trash entity
	entity = this->entityManager->CreateEntity(ENEMY);
	entity->SetTag(ENEMY);

	// Set up the sprite component
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, texturePath.c_str(), &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 256;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 256;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);

	// Set up the transform component
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = position;
	transformComponent->scale = D3DXVECTOR2(0.25 * size, 0.25 * size);

	// Set up the collider component
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({
			D3DXVECTOR2(-118, 91),	//A    
			D3DXVECTOR2(-53, 108),  //B  
			D3DXVECTOR2(53, 108),   //C  
			D3DXVECTOR2(118, 91),   //D  
			D3DXVECTOR2(118, 38),   //E 
			D3DXVECTOR2(53, 0),     //F  
			D3DXVECTOR2(-53, 0),    //G  
			D3DXVECTOR2(-118, 38)   //H  
		});
	//polygon2dColliderComponent->collsionEventScript = std::make_shared<PrintStringEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->friction = .2f;
	rigidbodyComponent->mass = 100.0f * (size);
	rigidbodyComponent->restitution = 1.0f; //0.3f
}

void GameScene::ToggleFullscreen()
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

void GameScene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> scene_manager)
{
	auto playerSprite = std::dynamic_pointer_cast<Sprite2DRendererComponent>(playerEntity->renderer);

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
		scene_manager->UnloadScene(true);
		scene_manager->LoadScene(PAUSE_MENU);
		return;
	}

	//FULLSCREEN WHEN RELEASE
	bool currentFKeyState = (diKeys[DIK_F] & 0x80) != 0;
	if (!currentFKeyState && fullscreenTriggered)
	{
		// The F key was just released
		ToggleFullscreen();
	}
	fullscreenTriggered = currentFKeyState;

	/*if (diKeys[DIK_F] & 0x80)
	{
		ToggleFullscreen();
	}*/


#pragma region PLAYER_KEYBOARD_INPUTS
	// player inputs
	auto e = playerEntity;
	auto t = e->transform;
	auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(e->rigidbody);
	D3DXVECTOR2 forceApplied = D3DXVECTOR2(0, 0);


	//forceApplied.x = sin(t->rotation) * thrust;
	//forceApplied.y = -cos(t->rotation) * thrust;
	//t->rotation -= framesToUpdate * rotationSpeed;

	//PLAYER MOVEMENT ===================
	int lastKey = -1;
	if (diKeys[DIK_W] & 0x80 || diKeys[DIK_S] & 0x80 || diKeys[DIK_A] & 0x80 || diKeys[DIK_D] & 0x80)
	{
		isMoving = true;
		if (diKeys[DIK_W] & 0x80)
		{
			forceApplied += D3DXVECTOR2(0, -1);
			lastKey = DIK_W;
		}
		if (diKeys[DIK_S] & 0x80)
		{
			forceApplied += D3DXVECTOR2(0, 1);
			lastKey = DIK_S;
		}
		if (diKeys[DIK_A] & 0x80)
		{
			forceApplied += D3DXVECTOR2(-1, 0);
			lastKey = DIK_A;
		}
		if (diKeys[DIK_D] & 0x80)
		{
			forceApplied += D3DXVECTOR2(1, 0);
			lastKey = DIK_D;
		}
	}
	//Player direction will be last key pressed
	switch (lastKey) {
	case DIK_W:
		playerSprite->spriteInfo.currentDirection = spriteInfo.upDirectionValue;
		break;
	case DIK_S:
		playerSprite->spriteInfo.currentDirection = spriteInfo.downDirectionValue;
		break;
	case DIK_A:
		playerSprite->spriteInfo.currentDirection = spriteInfo.leftDirectionValue;
		std::dynamic_pointer_cast<TrashHitEventScript>(attackColliderL->collsionEventScript)->isAttackingLeft = true;
		std::dynamic_pointer_cast<TrashHitEventScript>(attackColliderR->collsionEventScript)->isAttackingLeft = true;
		break;
	case DIK_D:
		playerSprite->spriteInfo.currentDirection = spriteInfo.rightDirectionValue;
		std::dynamic_pointer_cast<TrashHitEventScript>(attackColliderL->collsionEventScript)->isAttackingLeft = false;
		std::dynamic_pointer_cast<TrashHitEventScript>(attackColliderR->collsionEventScript)->isAttackingLeft = false;
		break;
	default:
		isMoving = false;
		break;
	}
	playerSprite->spriteInfo.animating = isMoving;
	//=================================

	//change scene WHEN RELEASE
	bool currentLKeyState = (diKeys[DIK_L] & 0x80) != 0;
	if (!currentLKeyState && changeSceneTriggered)
	{
		isSwitchScene = true;
	}
	changeSceneTriggered = currentLKeyState;

	D3DXVec2Normalize(&forceApplied, &forceApplied);
	rgb->ApplyForce(forceApplied * thrust * framesToUpdate);


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
		audioManager.PlayAudio(audioEntityGameScene->audios[0], t->position.x, SCREEN_WIDTH); // pans left and right
		timeSinceLastSound = 0.0f; // Reset the timer
	}

	// Spawn trash entities
	timeSinceLastSpawn += deltaTime;
	if (timeSinceLastSpawn >= spawnInterval)
	{
		// Reset the timer
		timeSinceLastSpawn = 0.0f;
		
		float x = minRangeX + (std::rand() % (maxRangeX - minRangeX + 1));
		float y = minRangeY + (std::rand() % (maxRangeY - minRangeY + 1));

		float size = minSize + (std::rand() % (maxSize - minSize + 1));
		
		D3DXVECTOR2 randomPosition(x, y);

		// Call createTrashEntity
		if (currentTrashCount < spawnLimit) {
			createTrashEntity(randomPosition, "Assets/garbagebag.png", size); // Adjust texture path as needed
			currentTrashCount++;
		}
	}

	//Play sound only when movement starts and regulate it with deltaTime
	timeSinceLastSoundGameScene += deltaTime;
	static float timeSinceLastSoundGameScene = 0.0f;
 	if (isMoving && !wasMoving && timeSinceLastSound >= 0.5f) // 0.5 seconds between sounds
 	{
 		audioManager.PlayAudio(audioEntityGameScene->audios[0], t->position.x, SCREEN_WIDTH); // pans left and right
 		timeSinceLastSound = 0.0f; // Reset the timer
 	}

}

void GameScene::AddIntoScene()
{
	std::shared_ptr<Sprite2DRendererComponent> spriteComponent;
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<Rigidbody2DComponent> rigidbodyComponent;
	std::shared_ptr<Polygon2DColliderComponent> polygon2dColliderComponent;
	std::shared_ptr<Audio2DComponent> audioComponent;
	std::shared_ptr<Audio2DComponent> audioBGM;

	audioEntityGameScene = this->entityManager->CreateEntity(AUDIO);
	audioComponent = this->componentManager->CreateAudio2DComponent(audioEntityGameScene);
	audioBGM = this->componentManager->CreateAudio2DComponent(audioEntityGameScene);
	audioComponent->LoadSound("Assets/Sounds/right-gravel-footstep-2.wav", false,false);  // [0]
	audioBGM->LoadSound("Assets/Sounds/jazz-loop.mp3", true, false); // [1]

	playerEntity = this->entityManager->CreateEntity(PLAYER);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(playerEntity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/militia.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 48;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 32;
	spriteInfo.totalRows = 4;
	spriteInfo.totalCols = 4;
	spriteInfo.isAnimated = true;
	spriteInfo.isDirectional = true;
	spriteInfo.fpsFactor = 3;
	spriteInfo.upDirectionValue = 3;
	spriteInfo.leftDirectionValue = 1;
	spriteInfo.rightDirectionValue = 2;
	spriteInfo.downDirectionValue = 0;
	spriteComponent->InitSpriteInfo(spriteInfo);

	transformComponent = this->componentManager->CreateTransformComponent(playerEntity);
	transformComponent->position = D3DXVECTOR2(1500, 100);
	transformComponent->scale = D3DXVECTOR2(2, 2);

	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(playerEntity);
	rigidbodyComponent->friction = 1.5f;
	rigidbodyComponent->mass = 100;
	rigidbodyComponent->restitution = 0.0f;
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(playerEntity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-16, -24), D3DXVECTOR2(16, -24), D3DXVECTOR2(16, 24), D3DXVECTOR2(-16, 24) });

	attackColliderL = this->componentManager->CreatePolygon2DColliderComponent(playerEntity);
	attackColliderL->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-48, -24), D3DXVECTOR2(0, -24), D3DXVECTOR2(0, 24), D3DXVECTOR2(-48, 24) });
	attackColliderL->isEventTrigger = true;
	attackColliderL->collsionEventScript = std::make_shared<TrashHitEventScript>();
	std::dynamic_pointer_cast<TrashHitEventScript>(attackColliderL->collsionEventScript)->isLeft = true;

	attackColliderR = this->componentManager->CreatePolygon2DColliderComponent(playerEntity);
	attackColliderR->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(48, -24), D3DXVECTOR2(0, -24), D3DXVECTOR2(0, 24), D3DXVECTOR2(48, 24) });
	attackColliderR->isEventTrigger = true;
	attackColliderR->collsionEventScript = std::make_shared<TrashHitEventScript>();
	std::dynamic_pointer_cast<TrashHitEventScript>(attackColliderR->collsionEventScript)->isLeft = false;


	// Trash bag ( Change to ball )
	entity = this->entityManager->CreateEntity(ENEMY);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/garbagebag.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 256;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 256;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(400, 400);
	transformComponent->scale = D3DXVECTOR2(0.25, 0.25);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({
	D3DXVECTOR2(-118, 91),	//A    
	D3DXVECTOR2(-53, 108),  //B  
	D3DXVECTOR2(53, 108),   //C  
	D3DXVECTOR2(118, 91),   //D  
	D3DXVECTOR2(118, 38),   //E 
	D3DXVECTOR2(53, 0),     //F  
	D3DXVECTOR2(-53, 0),    //G  
	D3DXVECTOR2(-118, 38)   //H  
		});
	//polygon2dColliderComponent->collsionEventScript = std::make_shared<PrintStringEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->friction = 0.2f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = 0.9f;
	octagonCollider = polygon2dColliderComponent;


	// Garbage truck collider
	entity = this->entityManager->CreateEntity(OBSTACLE);
	entity->SetTag(OBSTACLE);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/garbagetruck.png", &spriteInfo.texture);
	spriteInfo.sheetHeight = spriteInfo.spriteHeight = 189;
	spriteInfo.sheetWidth = spriteInfo.spriteWidth = 364;
	spriteInfo.totalRows = 1;
	spriteInfo.totalCols = 1;
	spriteInfo.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfo);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(1880, 400);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-71, 95), D3DXVECTOR2(-71, -95),
												D3DXVECTOR2(183, -95),D3DXVECTOR2(183, 95) });
	//polygon2dColliderComponent->collsionEventScript = std::make_shared<PrintStringEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;
	truckCollider = polygon2dColliderComponent;


	// Truck score collider
	goalEntity = this->entityManager->CreateEntity(GOAL);
	goalEntity->SetTag(GOAL);

	transformComponent = this->componentManager->CreateTransformComponent(goalEntity);
	transformComponent->position = D3DXVECTOR2(1680, 400);
	transformComponent->scale = D3DXVECTOR2(1, 1);

	truckGoalCollider = this->componentManager->CreatePolygon2DColliderComponent(goalEntity);
	truckGoalCollider->vertices = std::vector<D3DXVECTOR2>({
		D3DXVECTOR2(-100, -500), D3DXVECTOR2(100, -500), D3DXVECTOR2(100, 700),D3DXVECTOR2(-100, 700) });
	truckGoalCollider->collsionEventScript = std::make_shared<ScorePointEventScript>();
	truckGoalCollider->isEventTrigger = true;

	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(goalEntity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;

}

void GameScene::InitSceneAudio()
{
	audioManager.PlayAudio(audioEntityGameScene->audios[1], 0, 0);
}


