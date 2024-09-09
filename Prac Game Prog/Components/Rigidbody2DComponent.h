#pragma once

#include "../Systems/Core/Globals.h"
#include "RigidbodyComponent.h"

class Rigidbody2DComponent : public RigidbodyComponent
{
public:
    float mass, friction;
    D3DXVECTOR2 forceApplied = D3DXVECTOR2(0,0);
    D3DXVECTOR2 acceleration = D3DXVECTOR2(0,0);
    D3DXVECTOR2 maxAcceleration = D3DXVECTOR2(40,40);
    D3DXVECTOR2 velocity = D3DXVECTOR2(0,0);
    D3DXVECTOR2 maxVelocity = D3DXVECTOR2(999,999);
    bool bouncy;

    Rigidbody2DComponent();
    virtual ~Rigidbody2DComponent() = default;  // Virtual destructor
    void ApplyForce(D3DXVECTOR2 force);
};
