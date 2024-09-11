#include "SceneManager.h"



SceneManager::SceneManager()
{
    LoadScene(PAUSE_MENU);
    
}

void SceneManager::LoadScene(SceneEnum scene_enum)
{
    //SaveSceneData();
    
    // Push scene into stack
    switch (scene_enum)
    {
        case PAUSE_MENU:
            {
                auto menu = std::make_shared<PauseMenuScene>();
                menu->sceneName = PAUSE_MENU;
                auto entityManager = sceneEntityMap[menu->sceneName];
                if(entityManager != NULL)
                {
                    menu->entityManager = entityManager;
                }else
                {
                    menu->AddIntoScene();
                }
                auto componentManager = sceneComponentMap[menu->sceneName];
                if(componentManager != NULL)
                {
                    menu->componentManager = componentManager;
                }

                sceneStack.push(menu);
            }
            break;
        case MAIN_MENU:
            {
                auto menu = std::make_shared<MainMenuScene>();
                menu->sceneName = MAIN_MENU;
                auto entityManager = sceneEntityMap[menu->sceneName];
                if(entityManager != NULL)
                {
                    menu->entityManager = entityManager;
                }else
                {
                    menu->AddIntoScene();
                }
                auto componentManager = sceneComponentMap[menu->sceneName];
                if(componentManager != NULL)
                {
                    menu->componentManager = componentManager;
                }

                sceneStack.push(menu);
            }
            break;
        case GAME_SCENE:
            break;
    }
    
    currentScene = sceneStack.top();
}

void SceneManager::UnloadScene()
{
    if(!sceneStack.empty())
    {
        SaveSceneData();
 
        sceneStack.pop();

        if(!sceneStack.empty())
            this->currentScene = sceneStack.top();
        else
            this->currentScene = nullptr;
    }
}

void SceneManager::SaveSceneData()
{
    
        auto topScene = sceneStack.top();
        // Save popped out scene's data
        sceneComponentMap[topScene->sceneName] = topScene->componentManager; 
        sceneEntityMap[topScene->sceneName] = topScene->entityManager;
    
    
}

