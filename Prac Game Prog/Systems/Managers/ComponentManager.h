#pragma once
#include <map>
#include <vector>
#include "../../BaseClasses/Entity.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../Components/Rigidbody2DComponent.h"
#include "../../Components/Sprite2DRendererComponent.h"
#include "../../Enums/ComponentEnum.h"
#include "../Core/Globals.h"

typedef std::vector<std::shared_ptr<Component>> ComponentVector;
//  A map so we can get a vector of entities according to their tag
typedef std::map<ComponentEnum,ComponentVector> ComponentMap;

class ComponentManager
{
    
public:
    //TODO: need to change how to store components, lets not store pointers this time
    ComponentVector components;
    ComponentVector componentsToAdd;
    ComponentMap componentMap;
    size_t totalComponents = 0;
    
    void Start();
    void UpdateComponentList();
    void DoAllComponentStartups();
    void DoAllComponentUpdates();
    std::shared_ptr<TransformComponent> CreateTransformComponent(std::shared_ptr<Entity> parent);
    std::shared_ptr<NameComponent> CreateNameComponent(std::shared_ptr<Entity> parent);
    std::shared_ptr<Sprite2DRendererComponent> CreateSprite2DRendererComponent(std::shared_ptr<Entity> parent);
    std::shared_ptr<BoxColliderComponent> CreateBoxColliderComponent(std::shared_ptr<Entity> parent);
    std::shared_ptr<Rigidbody2DComponent> CreateRigidbody2DComponent(std::shared_ptr<Entity> parent);
    ComponentVector& GetComponents();
    ComponentVector& GetComponents(ComponentEnum componentTag);
    void DestroyAllComponents();
};
