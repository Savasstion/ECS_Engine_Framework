#pragma once
#include "../BaseClasses/Scene.h"
#include "SceneGlobals/GameSceneGlobals.h"
#include "../Scripts/EventScripts/TrashHitEventScript.h"
#include "../Scripts/EventScripts/ScorePointEventScript.h"



class GameScene : public Scene
{
public:
    GameScene();
    virtual ~GameScene() = default; //  virtual destructor
    void ToggleFullscreen();
    void createTrashEntity(const D3DXVECTOR2& position, const std::string& texturePath, const float size);
    void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;
    void InitSceneAudio()override;
private:
    float timeSinceLastSpawn = 0.0f;
    float spawnInterval = 2.5f;
    int minRangeX = 500, maxRangeX = SCREEN_WIDTH - 500;
    int minRangeY = 300, maxRangeY = SCREEN_HEIGHT - 300;

    int minSize = 1, maxSize = 3;

    int spawnLimit = 20;
};
