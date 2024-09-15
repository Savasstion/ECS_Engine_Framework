#include "OptionsScene.h"
#include "../Scripts/EventScripts/FullscreenButtonEventScript.h"
#include "../Scripts/EventScripts/OptionMenuQuitButtonEventScript.h"

OptionsScene::OptionsScene()
{
	Scene(OPTION_MENU);
}

void OptionsScene::ToggleFullscreen()
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

void OptionsScene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> sceneManager)
{
	optionSceneManager = sceneManager;

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

	// Sprite Animation Update															
	auto sprites = this->componentManager->GetComponents(SPRITE2D_RENDERER);
	for (auto component : sprites) {
		//std::cout << "Animating" << '\n';
		auto sprite2d = std::dynamic_pointer_cast<Sprite2DRendererComponent>(component);
		sprite2d->UpdateSpriteAnimation(framesToUpdate);
	}

}

void OptionsScene::AddIntoScene()
{
	std::shared_ptr<Sprite2DRendererComponent> spriteComponent;
	std::shared_ptr<TransformComponent> transformComponent;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<Rigidbody2DComponent> rigidbodyComponent;
	std::shared_ptr<Polygon2DColliderComponent> polygon2dColliderComponent;
	std::shared_ptr<Audio2DComponent> audioComponent;
	std::shared_ptr<Audio2DComponent> audioBGM;

	// Volume
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
	transformComponent->position = D3DXVECTOR2(200, 200);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	//polygon2dColliderComponent->collsionEventScript = std::make_shared<OptionButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .0f;
	rigidbodyComponent->mass = 1000000.0f;
	rigidbodyComponent->restitution = .7f;

	// Volume up and down button



	// Fullscreen
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
	transformComponent->position = D3DXVECTOR2(200, 300);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	polygon2dColliderComponent->collsionEventScript = std::make_shared<FullscreenButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .0f;
	rigidbodyComponent->mass = 1000000.0f;
	rigidbodyComponent->restitution = .7f;

	// Quit to pause menu
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
	transformComponent->position = D3DXVECTOR2(200, 400);
	transformComponent->scale = D3DXVECTOR2(1, 1);
	polygon2dColliderComponent = this->componentManager->CreatePolygon2DColliderComponent(entity);
	polygon2dColliderComponent->vertices = std::vector<D3DXVECTOR2>({ D3DXVECTOR2(-64, -23), D3DXVECTOR2(-64, 23), D3DXVECTOR2(64, 23), D3DXVECTOR2(64, -23) });
	polygon2dColliderComponent->collsionEventScript = std::make_shared<OptionMenuQuitButtonEventScript>();
	rigidbodyComponent = this->componentManager->CreateRigidbody2DComponent(entity);
	rigidbodyComponent->isStatic = true;
	rigidbodyComponent->friction = .0f;
	rigidbodyComponent->mass = 1000000.0f;
	rigidbodyComponent->restitution = .7f;

	// Mouse Pointer
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


	// Audio stuff

}
