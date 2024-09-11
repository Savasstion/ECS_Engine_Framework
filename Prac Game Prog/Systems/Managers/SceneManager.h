#pragma once
#include <memory>
#include <stack>
#include "../../Scenes/MainMenuScene.h"

class SceneManager
{
public:
    std::stack<std::shared_ptr<Scene>> sceneStack;
    std::shared_ptr<Scene> currentScene;

    SceneManager();
    std::shared_ptr<Scene> GetCurrentScene(){return currentScene;}
    //  for demo purpose, only one scene first, scene stack TO BE implemented
    //std::shared_ptr<Scene> AddNewScene()

    
};
