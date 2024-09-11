#include "Scene.h"

Scene::Scene()
{
    this->sceneName = "DEFAULT_LEVEL";
    this->entityManager = std::make_shared<EntityManager>();
    this->componentManager = std::make_shared<ComponentManager>();
}

Scene::Scene(std::string sceneName)
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
    sceneName.clear();
    entityManager->DestroyAllEntities();
    componentManager->DestroyAllComponents();
}

void Scene::UpdateScene(int framesToUpdate, float deltaTime)
{
}

void Scene::AddIntoScene()
{
}
