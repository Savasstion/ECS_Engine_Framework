#include "GameScene.h"

#include "SceneGlobals/GameSceneGlobals.h"

GameScene::GameScene()
{
    Scene(GAME_SCENE);
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
    bool isMoving = false;
    static bool wasMoving = false; // Track the previous movement state

    // Update timeSinceLastSound
    timeSinceLastSoundgameScene += deltaTime;

    //	Acquire the device.
    dInputKeyboardDevice->Acquire();
    dInputMouseDevice->Acquire();
}

void GameScene::AddIntoScene()
{
    
}
