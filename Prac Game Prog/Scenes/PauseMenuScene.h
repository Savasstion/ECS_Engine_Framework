#pragma once
#include "../BaseClasses/Scene.h"
#include "../Scenes/SceneGlobals/PauseMenuGlobals.h"
#include "../Scripts/EventScripts/PrintStringEventScript.h"
#include "../Scripts/EventScripts/ResumeButtonEventScript.h"
#include "../Scripts/EventScripts/PauseMenuQuitButtonEventScript.h"


class PauseMenuScene : public Scene
{
public:
    PauseMenuScene();
    virtual ~PauseMenuScene() = default;
    void ToggleFullscreen();
    //  virtual destructor
    void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;
    void InitSceneAudio()override;
};
