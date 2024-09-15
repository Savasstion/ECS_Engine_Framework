#include "MainMenuScene.h"

#include "../Systems/Managers/SceneManager.h"
#include "../Systems/Managers/InputManager.h"


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


void MainMenuScene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> sceneManager)
{
	mainMenuSceneManager = sceneManager;

	// Update timeSinceLastSound
	timeSinceLastSoundMainMenu += deltaTime;

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();

	// Increment the world position
	//worldPosition.x += 100.0f * deltaTime; // Adjust speed as needed
	int speed = 200;

	background5Transform->position.x -= speed * deltaTime * parallaxFactor1;
	background5Transform2->position.x -= speed * deltaTime * parallaxFactor1;
	background4Transform->position.x -= speed * deltaTime * parallaxFactor2;
	background4Transform2->position.x -= speed * deltaTime * parallaxFactor2;
	background3Transform->position.x -= speed * deltaTime * parallaxFactor3;
	background3Transform2->position.x -= speed * deltaTime * parallaxFactor3;
	background2Transform->position.x -= speed * deltaTime * parallaxFactor4;
	background2Transform2->position.x -= speed * deltaTime * parallaxFactor4;
	background1Transform->position.x -= speed * deltaTime* parallaxFactor5;
	background1Transform2->position.x -= speed * deltaTime * parallaxFactor5;

	// Cycle backgrounds
	if (background5Transform->position.x < -SCREEN_WIDTH/2) {
		background5Transform->position.x = background5Transform2->position.x + SCREEN_WIDTH;
	}
	if (background5Transform2->position.x < -SCREEN_WIDTH/2) {
		background5Transform2->position.x = background5Transform->position.x + SCREEN_WIDTH;
	}
	//4
	if (background4Transform->position.x < -SCREEN_WIDTH/2) {
		background4Transform->position.x = background4Transform2->position.x + SCREEN_WIDTH;
	}
	if (background4Transform2->position.x < -SCREEN_WIDTH/2) {
		background4Transform2->position.x = background4Transform->position.x + SCREEN_WIDTH;
	}

	if (background3Transform->position.x < -SCREEN_WIDTH/2) {
		background3Transform->position.x = background3Transform2->position.x + SCREEN_WIDTH;
	}
	if (background3Transform2->position.x < -SCREEN_WIDTH/2) {
		background3Transform2->position.x = background3Transform->position.x + SCREEN_WIDTH;
	}

	if (background2Transform->position.x < -SCREEN_WIDTH/2) {
		background2Transform->position.x = background2Transform2->position.x + SCREEN_WIDTH;
	}
	if (background2Transform2->position.x < -SCREEN_WIDTH/2) {
		background2Transform2->position.x = background2Transform->position.x + SCREEN_WIDTH;
	}

	if (background1Transform->position.x < -SCREEN_WIDTH/2) {
		background1Transform->position.x = background1Transform2->position.x + SCREEN_WIDTH;
	}
	if (background1Transform2->position.x < -SCREEN_WIDTH/2) {
		background1Transform2->position.x = background1Transform->position.x + SCREEN_WIDTH;
	}


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

	// Entities Boundaries
	auto entities = this->entityManager->GetEntities();
	for (auto e : entities) {
		if (e->transform != nullptr && e->GetTag() != BACKGROUND) {
			if (e->transform->position.x < 0) {
				e->transform->position.x = 0;
			}
			if (e->transform->position.x > SCREEN_WIDTH) {
				e->transform->position.x = SCREEN_WIDTH;
			}
			if (e->transform->position.y < 0) {
				e->transform->position.y = 0;
			}
			if (e->transform->position.y > SCREEN_HEIGHT) {
				e->transform->position.y = SCREEN_HEIGHT;
			}
		}
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
	transformComponent->position = D3DXVECTOR2((0), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((0), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((0), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((0), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2((SCREEN_WIDTH), (SCREEN_HEIGHT / 2));
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
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH / 2, 700);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23)});
	polygon2dColliderComponent->collsionEventScript = std::make_shared<MainMenuPlayButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;
	
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
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH / 2, 800);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	polygon2dColliderComponent->collsionEventScript = std::make_shared<OptionButtonEventScript>();
	polygon2dColliderComponent->isEventTrigger = true;
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;
	

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
	transformComponent->position = D3DXVECTOR2(SCREEN_WIDTH / 2, 900);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	polygon2dColliderComponent->collsionEventScript = std::make_shared<MainMenuQuitButtonEventScript>();
	polygon2dColliderComponent->isEventTrigger = true;
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;

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
	polygon2dColliderComponent->relativePos = D3DXVECTOR2(-8, -8);
	polygon2dColliderComponent->isEventTrigger = true;
	mousePointerCollider = polygon2dColliderComponent;
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .5f;
	rigidbodyComponent->mass = 1.0f;
	rigidbodyComponent->restitution = .3f;
	
}

void MainMenuScene::InitSceneAudio()
{
	audioManager.PlayAudio(audioEntityMainMenu->audios[1], 0, 0);
}


