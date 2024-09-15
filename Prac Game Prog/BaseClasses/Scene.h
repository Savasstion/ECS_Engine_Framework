#pragma once
#include <string>

#include "../Enums/SceneEnum.h"
#include "../Systems/Managers/ComponentManager.h"
#include "../Systems/Managers/EntityManager.h"
#include "../Systems/Core/Audio.h"
#include <memory>

class SceneManager;

class Scene
{
public:
    //testing
    bool isSwitchScene = false;
    
    SceneEnum sceneName;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<ComponentManager> componentManager;
    //Audio audioManager;


    Scene();
    Scene(SceneEnum sceneName);
    void BeginScene();
    void EndScene();
    virtual void UpdateScene(int framesToUpdate,float deltaTime, std::shared_ptr<SceneManager> scene_manager); //  implement and override in child class
    virtual void AddIntoScene();
    //testing
    void SwitchScene(std::shared_ptr<SceneManager> scene_manager, SceneEnum sceneName);
    virtual void InitSceneAudio();
};
