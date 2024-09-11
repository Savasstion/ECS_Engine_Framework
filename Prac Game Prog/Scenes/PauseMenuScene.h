#pragma once
#include "../BaseClasses/Scene.h"
#include "../Scenes/SceneGlobals/MainMenuGlobals.h"
#include "../Scripts/EventScripts/PrintStringEventScript.h"


class PauseMenuScene : public Scene
{
public:
    PauseMenuScene();
    virtual ~PauseMenuScene() = default; //  virtual destructor
    void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager)override;
    void AddIntoScene()override;

};
