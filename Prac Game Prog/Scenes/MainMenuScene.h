#pragma once
#include "../BaseClasses/Scene.h"
#include "../Scenes/SceneGlobals/MainMenuGlobals.h"
#include "../Scripts/EventScripts/PrintStringEventScript.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene();
    virtual ~MainMenuScene() = default; //  virtual destructor
    void UpdateScene(int framesToUpdate,float deltaTime)override;
    void AddIntoScene()override;
};
