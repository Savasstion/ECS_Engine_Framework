#include "Rigidbody2DComponent.h"
#include "../BaseClasses/Entity.h"

Rigidbody2DComponent::Rigidbody2DComponent()
{
    Component(RIGIDBODY2D);
    mass = 1;
    friction = 0.1f;
    isStatic = false;
}

void Rigidbody2DComponent::ApplyForce(D3DXVECTOR2 force)
{
    forceApplied += force;

   /* if (mass != 0) {
        acceleration = forceApplied / mass;*/
    //} else {
        //acceleration = D3DXVECTOR2(0, 0); // Prevent division by zero
    //}
}
