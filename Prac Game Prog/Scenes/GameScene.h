#pragma once
#include "../BaseClasses/Scene.h"

class GameScene : public Scene
{
public:
    GameScene();
    virtual ~GameScene() = default; //  virtual destructor
    void ToggleFullscreen();
    void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;
};
