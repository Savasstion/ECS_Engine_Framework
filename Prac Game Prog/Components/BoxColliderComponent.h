#pragma once
#include "ColliderComponent.h"
#include "d3d9.h"

enum class ColliderTag {
    Player,
    Enemy,
    PowerUp,
};

class BoxColliderComponent : public ColliderComponent
{
public:
    RECT box;
    ColliderTag tag;
    BoxColliderComponent();
    BoxColliderComponent(RECT box, ColliderTag tag = ColliderTag::Player);
    virtual ~BoxColliderComponent() = default;  // Virtual destructor
    
};
