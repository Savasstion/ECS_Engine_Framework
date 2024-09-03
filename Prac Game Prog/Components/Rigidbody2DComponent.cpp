#include "Rigidbody2DComponent.h"
#include "../BaseClasses/Entity.h"

Rigidbody2DComponent::Rigidbody2DComponent()
{
    Component(RIGIDBODY2D);
    mass = 1;
    friction = 0.5;
}

void Rigidbody2DComponent::ApplyForce(D3DXVECTOR2 force)
{
    acceleration = force / mass;
    
}

void Rigidbody2DComponent::DoCycleOfMotion()
{
    velocity += acceleration;
    velocity *= (1 - friction);

    if(parent->transform != nullptr)
        parent->transform->position += velocity; 
}
