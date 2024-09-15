#pragma once
#include "../EventScript.h"
#include "../../BaseClasses/Entity.h"
#include "../../Components/ColliderComponent.h"
#include "../../Components/Rigidbody2DComponent.h"
#include  "../../Systems/Managers/InputManager.h"

class TrashHitEventScript: public EventScript
{
public:
    float forceMagnitude = 2250;
    bool isLeft;
    bool isAttackingLeft;
    
    void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)override;
};
