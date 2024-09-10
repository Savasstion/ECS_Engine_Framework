#pragma once
#include "ColliderComponent.h"
#include "d3d9.h"
#include "../Enums/ColliderTag.h"

//  Greg's Collider
//  TODO: get this working one day
// enum class ColliderTag {
//     Player,
//     Enemy,
//     PowerUp,
// };

class BoxColliderComponent : public ColliderComponent
{
public:
    RECT box;
    ColliderTag tag;
    BoxColliderComponent();
    BoxColliderComponent(RECT box, ColliderTag tag = ColliderTag::DEFAULT_COLLIDER);
    void SetBox(RECT box, D3DXVECTOR2 centerPos);
    void SetColliderTag(ColliderTag tag){this->tag = tag;}
    void UpdateColliderPos(D3DXVECTOR2 velocity) override;
    virtual ~BoxColliderComponent() = default;  // Virtual destructor
    
};
