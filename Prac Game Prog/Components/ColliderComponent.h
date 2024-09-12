#pragma once
#include <d3dx9math.h>
#include "../BaseClasses/Component.h"
#include "../Scripts/EventScript.h"
#include "../BaseClasses/CollisionEvent.h"


class ColliderComponent : public Component
{
public:
    D3DXVECTOR2 relativePos = D3DXVECTOR2(0,0);
    bool isVisible = false;
    //std::shared_ptr<CollisionEvent> collisionEvent = std::make_shared<CollisionEvent>();
    std::shared_ptr<EventScript> collsionEventScript;

    long AddCollisionListener();
    virtual ~ColliderComponent() = default;  // Virtual destructor
    virtual void UpdateColliderPos(D3DXVECTOR2 parentPos);


};
