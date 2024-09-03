#include "SceneManager.h"

SceneManager::SceneManager()
{
    this->currentScene = std::make_shared<Scene>();
    
}
