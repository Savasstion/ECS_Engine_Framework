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
    void createTrashEntity(const D3DXVECTOR2& position, const std::string& texturePath);
    void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;
private:
    float timeSinceLastSpawn = 0.0f;
    float spawnInterval = 8.0f;
};
