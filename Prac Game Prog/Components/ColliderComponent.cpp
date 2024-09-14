#include "ColliderComponent.h"

#include "../BaseClasses/Entity.h"


// long ColliderComponent::AddCollisionListener()
// {
//     long id = Event::GetNewEventListenerID();
//     collisionEvent->AddListener(id,std::bind(&EventScript::RunScript, collsionEventScript, collisionEvent->ownerCollider, collisionEvent->incomingCollider));
//     return id;
// }

void ColliderComponent::UpdateColliderPos(D3DXVECTOR2 velocity)
{
}

void ColliderComponent::DoAllExitCollisions()
{
    //  Do All Exit Collision eventsd
    for (auto collider : prevTriggeredColliders) {
        if (currentTriggeredColliders.find(collider) == currentTriggeredColliders.end()) {
            // If collider is not found in currentSet, it means collision has exited
            if( collider->collsionEventScript != nullptr)
                collider->collsionEventScript->DoExitCollisionScript(collider);
        }
    }
}
