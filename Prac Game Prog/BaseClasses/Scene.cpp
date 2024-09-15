#include "Scene.h"

#include "../Systems/Managers/SceneManager.h"

Scene::Scene()
{
    this->sceneName = DEFAULT_SCENE;
    this->entityManager = std::make_shared<EntityManager>();
    this->componentManager = std::make_shared<ComponentManager>();
}

Scene::Scene(SceneEnum sceneName)
{
    this->sceneName = sceneName;
    this->entityManager = std::make_shared<EntityManager>();
    this->componentManager = std::make_shared<ComponentManager>();
}

void Scene::BeginScene()
{
}

void Scene::EndScene()
{
    entityManager->DestroyAllEntities();
    componentManager->DestroyAllComponents();
}

void Scene::UpdateScene(int framesToUpdate, float deltaTime, std::shared_ptr<SceneManager> scene_manager)
{
}

void Scene::AddIntoScene()
{
}

void Scene::SwitchScene(std::shared_ptr<SceneManager> scene_manager, SceneEnum sceneName)
{
    //Switch scene
    scene_manager->UnloadScene(true);
    scene_manager->LoadScene(sceneName);

}

void Scene::InitSceneAudio()
{
}

