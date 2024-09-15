#pragma once
#include "../EventScript.h"

class VolumeChangeButtonEventScript : public EventScript
{
public:
    bool isIncrementVolume;
    
    void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)override;

};
