#include "PrintStringEventScript.h"

#include <iostream>

void PrintStringEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
                                       std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    
}

void PrintStringEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
    //std::cout << "Start to Blow up world\n";
}

void PrintStringEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(ownerCollider, incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
