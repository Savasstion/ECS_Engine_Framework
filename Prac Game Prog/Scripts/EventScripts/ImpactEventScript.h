#pragma once
#include "../EventScript.h"
#include <d3dx9math.h>

class ImpactEventScript : public EventScript
{
public:
    void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider)override;

    bool isLanded = false, isImpactFrame = false;

    D3DXVECTOR2 landingPos = D3DXVECTOR2(0, 0);

};
