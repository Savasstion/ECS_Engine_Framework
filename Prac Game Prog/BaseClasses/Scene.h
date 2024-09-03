#pragma once
#include <string>

#include "../Systems/Managers/ComponentManager.h"
#include "../Systems/Managers/EntityManager.h"

class Scene
{
public:
    std::string sceneName;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<ComponentManager> componentManager;
    //  Assets :
    //  vector<Sprite>

    Scene();
    void BeginScene();
    void EndScene();
};
