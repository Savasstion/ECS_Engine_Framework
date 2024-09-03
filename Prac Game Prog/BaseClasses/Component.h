#pragma once

#include <memory>

#include "../Enums/ComponentEnum.h"

class Entity;
class Component
{
public:
    ComponentEnum componentType;
    bool isActive = true;
    std::shared_ptr<Entity> parent;

    virtual ~Component() = default;  // Virtual destructor
    Component();
    Component(ComponentEnum componentType);
    void Start();
    void Update();
    ComponentEnum GetComponentTag(){return componentType;}
    bool GetIsActive(){return isActive;}
    void Destroy();
};
