#pragma once
#include "../BaseClasses/Scene.h"
#include "../Scenes/SceneGlobals/MainMenuGlobals.h"
#include "../Scripts/EventScripts/PrintStringEventScript.h"
#include "../Scripts/EventScripts/ImpactEventScript.h"
#include "../Scripts/EventScripts/OptionButtonEventScript.h"
#include "../Scripts/EventScripts/MainMenuQuitButtonEventScript.h"
#include "../Scripts/EventScripts/MainMenuPlayButtonEventScript.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene();
    virtual ~MainMenuScene() = default; //  virtual destructor
    void ToggleFullscreen();
    void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;
    void InitSceneAudio()override;
};
