#include "ScorePointEventScript.h"
#include <iostream>

void ScorePointEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";

}

void ScorePointEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
    std::cout << "Point Score!\n";

    if (incomingCollider->parent->GetTag() == ENEMY)
    {
        incomingCollider->parent->Destroy();
    }

}

void ScorePointEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider)
{
    EventScript::DoExitCollisionScript(ownerCollider);
    //std::cout << "Stop Blowing up world\n";
}