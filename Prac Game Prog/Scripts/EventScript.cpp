#include "EventScript.h"
#include "../Components/ColliderComponent.h"

void EventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if(!isDoneOnce)
    {
        DoEnterCollisionScript(ownerCollider, incomingCollider);
    }
}

void EventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    isDoneOnce = true;
}

void EventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    isDoneOnce = false; //reset
}


