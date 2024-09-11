#include "ColliderComponent.h"



void ColliderComponent::AddCollisionListener()
{
    collisionEvent->AddListener(std::bind(&EventScript::RunScript, collsionEventScript, collisionEvent->ownerCollider, collisionEvent->incomingCollider));
}

void ColliderComponent::UpdateColliderPos(D3DXVECTOR2 velocity)
{
}
