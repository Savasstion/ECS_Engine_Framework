#pragma once
#include <memory>

#include "../../BaseClasses/Scene.h"

class SceneManager
{
public:
    std::shared_ptr<Scene> currentScene;

    SceneManager();
    std::shared_ptr<Scene> GetCurrentScene(){return currentScene;}
    //  for demo purpose, only one scene first, scene stack TO BE implemented
    //std::shared_ptr<Scene> AddNewScene()
    
};
