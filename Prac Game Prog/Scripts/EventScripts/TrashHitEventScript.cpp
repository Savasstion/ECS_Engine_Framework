#include "TrashHitEventScript.h"



void TrashHitEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
                                    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    
}

void TrashHitEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
    //stuff
    
    //if(attackTriggered)
        if(incomingCollider->parent->GetTag() == ENEMY)
        {
            D3DXVECTOR2 playerToEnemyDir;
            playerToEnemyDir = incomingCollider->parent->transform->position - ownerCollider->parent->transform->position;
            D3DXVec2Normalize(&playerToEnemyDir, &playerToEnemyDir);

            if(incomingCollider->parent->rigidbody != nullptr)
            {
                auto enemyRGB2d = std::dynamic_pointer_cast<Rigidbody2DComponent>(incomingCollider->parent->rigidbody);
                enemyRGB2d->ApplyForce(playerToEnemyDir * forceMagnitude);
                std::cout << "Trash hit" << std::endl;
            }
        }
        
}

void TrashHitEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider)
{
    EventScript::DoExitCollisionScript(ownerCollider);
    //stuff
    std::cout << "Trash exit" << std::endl;
}