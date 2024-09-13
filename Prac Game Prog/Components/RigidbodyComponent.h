#pragma once
#include "../BaseClasses/Component.h"

class RigidbodyComponent : public Component
{
public:
    float mass = 1;
    float friction;
    float restitution = 0;
    bool isStatic = false;
    virtual ~RigidbodyComponent() = default;  // Virtual destructor
    
};
