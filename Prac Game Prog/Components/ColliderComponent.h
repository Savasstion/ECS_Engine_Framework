#pragma once
#include <d3dx9math.h>
#include <set>

#include "../BaseClasses/Component.h"
#include "../Scripts/EventScript.h"
#include "../BaseClasses/CollisionEvent.h"



class ColliderComponent : public Component
{
public:
    bool isEventTrigger = false; // if false, physics response will be done, if true, only just call event trigger
    D3DXVECTOR2 relativePos = D3DXVECTOR2(0,0);
    bool isVisible = false;
    //std::shared_ptr<CollisionEvent> collisionEvent = std::make_shared<CollisionEvent>();
    std::shared_ptr<EventScript> collsionEventScript;
    //  check if there are elements from current Set missing in prev Set
    //  if so, means exit collision event should occur for those elements
    std::set<std::shared_ptr<ColliderComponent>> currentTriggeredColliders;
    std::set<std::shared_ptr<ColliderComponent>> prevTriggeredColliders;   

    //long AddCollisionListener();
    virtual ~ColliderComponent() = default;  // Virtual destructor
    virtual void UpdateColliderPos(D3DXVECTOR2 parentPos);
    void DoAllExitCollisions();


};
