#include "ComponentManager.h"

#include <memory>

#include "../../Components/BoxColliderComponent.h"
#include "../../Components/Sprite2DRendererComponent.h"

void ComponentManager::Start()
{
   DoAllComponentStartups();
}

void ComponentManager::UpdateComponentList()
{
    //look at entity manager cpp to get the same idea/comments implemented here
    for(auto c : componentsToAdd)
    {
        components.push_back(c);
        componentMap[c->GetComponentTag()].push_back(c);
    }

    for(auto c : componentsToAdd)
    {
        c->Start();
    }
    componentsToAdd.clear();

    //  check all entities if not active, remove from main lists
    for(auto c : components)
    {
        if(!c->GetIsActive())
        {
            //  move e to the end of vector and change the end of vector to leave out e
            components.erase(std::remove(components.begin(), components.end(), c), components.end());
            componentMap[c->GetComponentTag()].erase(std::remove(componentMap[c->GetComponentTag()].begin(), componentMap[c->GetComponentTag()].end(), c), componentMap[c->GetComponentTag()].end());
        }
    }
    
    
}

void ComponentManager::DoAllComponentStartups()
{
    for(auto c : components)
    {
        c->Start();
    }
}

void ComponentManager::DoAllComponentUpdates()
{
    //  do all entity updates
    for(auto c : components)
    {
        c->Update();
    }
}

std::shared_ptr<TransformComponent> ComponentManager::CreateTransformComponent(std::shared_ptr<Entity> parent)
{
    auto a = std::make_shared<TransformComponent>();
    a->parent = parent;
    parent->transform = a;
    componentsToAdd.push_back(a);
    componentMap[TRANSFORM].push_back(a);
    return a;
}

std::shared_ptr<NameComponent> ComponentManager::CreateNameComponent(std::shared_ptr<Entity> parent)
{
    auto b = std::make_shared<NameComponent>();
    b->parent = parent;
    parent->name = b;
    componentsToAdd.push_back(b);
    componentMap[NAME].push_back(b);
    return b;
}

std::shared_ptr<Sprite2DRendererComponent> ComponentManager::CreateSprite2DRendererComponent(
    std::shared_ptr<Entity> parent)
{
    auto c = std::make_shared<Sprite2DRendererComponent>();
    c->componentType = SPRITE2D_RENDERER;
    c->parent = parent;
    parent->renderer = c;
    componentsToAdd.push_back(c);
    componentMap[SPRITE2D_RENDERER].push_back(c);
    return c;
}

std::shared_ptr<BoxColliderComponent> ComponentManager::CreateBoxColliderComponent(std::shared_ptr<Entity> parent)
{
    auto c = std::make_shared<BoxColliderComponent>();
    c->parent = parent;
    parent->colliders.push_back(c);
    componentsToAdd.push_back(c);
    componentMap[BOX_COLLIDER].push_back(c);
    return c;
}

std::shared_ptr<Rigidbody2DComponent> ComponentManager::CreateRigidbody2DComponent(std::shared_ptr<Entity> parent)
{
    auto c = std::make_shared<Rigidbody2DComponent>();
    c->parent = parent;
    parent->rigidbody = c;
    componentsToAdd.push_back(c);
    componentMap[RIGIDBODY2D].push_back(c);
    return c;
}

std::shared_ptr<Audio2DComponent> ComponentManager::CreateAudio2DComponent(std::shared_ptr<Entity> parent)
{
    auto c = std::make_shared<Audio2DComponent>();
    c->parent = parent;
    parent->audios.push_back(c);
    componentsToAdd.push_back(c);
    componentMap[AUDIO2D].push_back(c);
    return c;
}

ComponentVector& ComponentManager::GetComponents()
{
    return components;
}

ComponentVector& ComponentManager::GetComponents(ComponentEnum componentTag)
{
    return componentMap[componentTag];
}

void ComponentManager::DestroyAllComponents()
{
    for(auto c : components)
    {
        c->Destroy();
    }
}
