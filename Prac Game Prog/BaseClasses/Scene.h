#pragma once
#include <string>

#include "../Systems/Managers/ComponentManager.h"
#include "../Systems/Managers/EntityManager.h"
#include "../Systems/Core/Audio.h"

class Scene
{
public:
    std::string sceneName;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<ComponentManager> componentManager;
    //Audio audioManager;


    Scene();
    Scene(std::string sceneName);
    void BeginScene();
    void EndScene();
    virtual void UpdateScene(int framesToUpdate,float deltaTime); //  implement and override in child class
    virtual void AddIntoScene();
};
