#pragma once
#include <memory>
#include "Event.h"


class ColliderComponent;

class CollisionEvent : public Event
{
public:
    std::shared_ptr<ColliderComponent> ownerCollider = nullptr;
    std::shared_ptr<ColliderComponent> incomingCollider = nullptr;
};
