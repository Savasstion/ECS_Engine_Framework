#include "ImpactEventScript.h"
#include <iostream>



void ImpactEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    if (isLanded == true){
        if (isImpactFrame == true) {
            // player take damage
            // player get knockback
           }
        isLanded = false;
        isImpactFrame = false;
    }
}

void ImpactEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
    if (isLanded == true) {
        isImpactFrame = true;
    }
   
}

void ImpactEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider)
{
    EventScript::DoExitCollisionScript(ownerCollider);
    std::cout << "Stop Blowing up world\n";
}