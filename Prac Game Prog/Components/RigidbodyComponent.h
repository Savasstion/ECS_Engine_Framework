#pragma once
#include "../BaseClasses/Component.h"

class RigidbodyComponent : public Component
{
public:
    //  TODO : force user to use a Setter for mass, friction and restitution because :
    //  Mass cannot be below 1
    //  Friction cant be a negative
    //  Restitution is a value between 0 and 1
    
    float mass = 1;
    float friction;
    //  restitution is the ratio of how much a body will bounce back. If 1 then full bounce with no loss of energy. If 0, no bounce at all
    float restitution = 0;
    bool isStatic = false;
    virtual ~RigidbodyComponent() = default;  // Virtual destructor
    
};
