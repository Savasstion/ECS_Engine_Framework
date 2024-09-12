#pragma once
#include <memory>
#include <stack>
#include <map>
#include <string>
#include "../../Scenes/MainMenuScene.h"
#include "../../Scenes/PauseMenuScene.h"


class SceneManager
{
public:
    std::stack<std::shared_ptr<Scene>> sceneStack;
    std::shared_ptr<Scene> currentScene;
    std::map<SceneEnum , std::shared_ptr<ComponentManager>> sceneComponentMap;
    std::map<SceneEnum , std::shared_ptr<EntityManager>> sceneEntityMap;

    SceneManager();
    std::shared_ptr<Scene> GetCurrentScene(){return currentScene;}
    //  for demo purpose, only one scene first, scene stack TO BE implemented
    //std::shared_ptr<Scene> AddNewScene()
    void LoadScene(SceneEnum scene_enu);
    void UnloadScene(bool isSaveSceneData);
    void SaveSceneData();
    
};
