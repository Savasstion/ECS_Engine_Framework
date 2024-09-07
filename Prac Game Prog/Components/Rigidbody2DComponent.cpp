#include "Rigidbody2DComponent.h"
#include "../BaseClasses/Entity.h"

Rigidbody2DComponent::Rigidbody2DComponent()
{
    Component(RIGIDBODY2D);
    mass = 1;
    friction = 0.1;
    bouncy = false;
}

void Rigidbody2DComponent::ApplyForce(D3DXVECTOR2 force)
{
    acceleration += force / mass;
}
