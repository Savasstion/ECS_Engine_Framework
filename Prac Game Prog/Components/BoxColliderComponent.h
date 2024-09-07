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
    void SetBox(RECT box){this->box = box;}
    void SetColliderTag(ColliderTag tag){this->tag = tag;}
    virtual ~BoxColliderComponent() = default;  // Virtual destructor
    
};
