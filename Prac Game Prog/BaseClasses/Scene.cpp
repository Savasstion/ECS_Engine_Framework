#include "Scene.h"

Scene::Scene()
{
    this->sceneName = "DEFAULT_LEVEL";
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
