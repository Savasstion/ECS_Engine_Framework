#pragma once
#include "../BaseClasses/Scene.h"
#include "../Scenes/SceneGlobals/OptionSceneGlobals.h"

class OptionsScene : public Scene
{
public:
    OptionsScene();
    virtual ~OptionsScene() = default; //  virtual destructor
    void ToggleFullscreen();
    void UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;
};