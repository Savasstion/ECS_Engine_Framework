#include "MainMenuScene.h"

#include "../Systems/Managers/SceneManager.h"
#include "../InputManager.h"


D3DXVECTOR2 worldPosition = D3DXVECTOR2(-SCREEN_WIDTH/2, 0);

MainMenuScene::MainMenuScene()
{
    Scene(MAIN_MENU);

}

void MainMenuScene::ToggleFullscreen()
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


void MainMenuScene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> scene_manager)
{
    //  update stuff
    
	bool isMoving = false;
	static bool wasMoving = false; // Track the previous movement state

	// Update timeSinceLastSound
	timeSinceLastSoundMainMenu += deltaTime;

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();

	// Increment the world position
	worldPosition.x += 20.0f * deltaTime; // Adjust speed as needed

	// Update the first set of background positions
	background1Transform->position.x = -int(worldPosition.x * parallaxFactor5) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background2Transform->position.x = -int(worldPosition.x * parallaxFactor4) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background3Transform->position.x = -int(worldPosition.x * parallaxFactor3) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background4Transform->position.x = -int(worldPosition.x * parallaxFactor2) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background5Transform->position.x = -int(worldPosition.x * parallaxFactor1) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;

	// Update the second set of background positions for seamless looping
	background1Transform2->position.x = -int(worldPosition.x * parallaxFactor5 + SCREEN_WIDTH) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background2Transform2->position.x = -int(worldPosition.x * parallaxFactor4 + SCREEN_WIDTH) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background3Transform2->position.x = -int(worldPosition.x * parallaxFactor3 + SCREEN_WIDTH) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background4Transform2->position.x = -int(worldPosition.x * parallaxFactor2 + SCREEN_WIDTH) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;
	background5Transform2->position.x = -int(worldPosition.x * parallaxFactor1 + SCREEN_WIDTH) % (SCREEN_WIDTH * 2) + SCREEN_WIDTH / 2;


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

	//FULLSCREEN WHEN RELEASE
	bool currentFKeyState = (diKeys[DIK_F] & 0x80) != 0;
	if (!currentFKeyState && fullscreenTriggered)
	{
		// The F key was just released
		ToggleFullscreen();
	}
	fullscreenTriggered = currentFKeyState;

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

	//testing
	if (diKeys[DIK_L] & 0x80)
	{
		
		isSwitchScene = true;
	}

	D3DXVec2Normalize(&forceApplied,&forceApplied);
	rgb->ApplyForce(forceApplied * mainMenuThrust * framesToUpdate);
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
		audioManager.PlayAudio(audioEntityMainMenu->audios[0], t->position.x, SCREEN_WIDTH); // pans left and right
		timeSinceLastSound = 0.0f; // Reset the timer
	}

	
}

void MainMenuScene::AddIntoScene()

{
	//	buffers for temporary assignment of data to the components
	std::shared_ptr<Sprite2DRendererComponent> spriteComponent;
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<Rigidbody2DComponent> rigidbodyComponent;
	std::shared_ptr<Polygon2DColliderComponent> polygon2dColliderComponent;
	std::shared_ptr<Audio2DComponent> audioComponent;
	std::shared_ptr<Audio2DComponent> audioBGM;


	//Parallax background attempt
	#pragma region parallaxbackground
	//Back layer
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/1.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH/2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background1Transform = transformComponent;
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/1.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH/2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background1Transform2 = transformComponent;

	
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/2.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background2Transform = transformComponent;
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/2.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH*2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background2Transform2 = transformComponent;


	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/3.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background3Transform = transformComponent;
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/3.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background3Transform2 = transformComponent;


	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/4.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background4Transform = transformComponent;
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/4.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background4Transform2 = transformComponent;


	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/5.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(0, (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background5Transform = transformComponent;
	entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/5.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH, (SCREEN_HEIGHT / 2));
	transformComponent->scale = D3DXVECTOR2(1, 1);
	background5Transform2 = transformComponent;
	#pragma endregion


	
	//Background
	/*entity = this->entityManager->CreateEntity(BACKGROUND);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/city 7/7.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = SCREEN_HEIGHT;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = SCREEN_WIDTH;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2));
	transformComponent->scale = D3DXVECTOR2(1, 1);*/

	
	// Test audio entity
	audioEntityMainMenu = this->entityManager->CreateEntity(BACKGROUND);
	audioComponent = this->componentManager->CreateAudio2DComponent(audioEntityMainMenu);
	audioBGM = this->componentManager->CreateAudio2DComponent(audioEntityMainMenu);
	audioComponent->LoadSound("Assets/Sounds/right-gravel-footstep-2.wav", false, false);  // [0]
	audioBGM->LoadSound("Assets/Sounds/jazz-loop.mp3", true, false); // [1]

	//MILITIA
	entity = this->entityManager->CreateEntity(PLAYER);

	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/militia.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = 48;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = 32;
	spriteInfoMainMenu.totalRows = 4;
	spriteInfoMainMenu.totalCols = 4;
	spriteInfoMainMenu.isAnimated = true;
	spriteInfo1MainMenu.isDirectional = true;
	spriteInfoMainMenu.upDirectionValue = 3;
	spriteInfoMainMenu.leftDirectionValue = 1;
	spriteInfoMainMenu.rightDirectionValue = 2;
	spriteInfoMainMenu.downDirectionValue = 0;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);

	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(500, 100);
	transformComponent->scale = D3DXVECTOR2(2, 2);

	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->friction = 0.5f;
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-16, -24), D3DXVECTOR2(16, -24), D3DXVECTOR2(16, 24), D3DXVECTOR2(-16, 24)});
	polygon2dColliderComponent->collsionEventScript = std::make_shared<PrintStringEventScript>(); //child class of EventScript btw
	//	for testing
	collider1 = polygon2dColliderComponent;
	// Audio stuff
	// this = current this, call componentManager to create Audio2DComponent, e = parent entity

	
	//UI stuff
	//Resume Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/playbutton.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = 45;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = 127;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 700);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23)});
	polygon2dColliderComponent->collsionEventScript = std::make_shared<ImpactEventScript>();
	
	//	for testing
	collider2 = polygon2dColliderComponent;

	//Options Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/optionsbutton.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = 45;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = 127;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 800);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	

	//Quit Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/quitbutton.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = 45;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = 127;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(200, 900);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });

	//Logo Button
	entity = this->entityManager->CreateEntity(UI);
	spriteComponent = this->componentManager->CreateSprite2DRendererComponent(entity);
	D3DXCreateTextureFromFile(d3dDevice, "Assets/UI/trshgame.png", &spriteInfoMainMenu.texture);
	spriteInfoMainMenu.sheetHeight = spriteInfoMainMenu.spriteHeight = 72;
	spriteInfoMainMenu.sheetWidth = spriteInfoMainMenu.spriteWidth = 580;
	spriteInfoMainMenu.totalRows = 1;
	spriteInfoMainMenu.totalCols = 1;
	spriteInfoMainMenu.isAnimated = false;
	spriteComponent->InitSpriteInfo(spriteInfoMainMenu);
	transformComponent = this->componentManager->CreateTransformComponent(entity);
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/6);
	transformComponent->scale = D3DXVECTOR2(1, 1);

	audioManager.PlayAudio(audioEntityMainMenu->audios[1], 0, 0);
	
}


