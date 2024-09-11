#include "ColliderComponent.h"


long ColliderComponent::AddCollisionListener()
{
    long id = Event::GetNewEventListenerID();
    collisionEvent->AddListener(id,std::bind(&EventScript::RunScript, collsionEventScript, collisionEvent->ownerCollider, collisionEvent->incomingCollider));
    return id;
}

void ColliderComponent::UpdateColliderPos(D3DXVECTOR2 velocity)
{
}
