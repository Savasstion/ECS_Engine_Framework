#pragma once
#include <vector>

#include "ColliderComponent.h"
#include "../Enums/ColliderTag.h"

class Polygon2DColliderComponent : public ColliderComponent
{
public:
    ColliderTag colliderTag;
    //  with respect to (0,0) as the center of collider
    //  also make sure vertex to vertex is sequentially consistent for line drawing
    std::vector<D3DXVECTOR2> vertices;  
    
    Polygon2DColliderComponent();
    virtual ~Polygon2DColliderComponent() = default;  // Virtual destructor
    ColliderTag GetTag(){return colliderTag;}
    void SetTag(ColliderTag tag){this->colliderTag = tag;}
    std::vector<D3DXVECTOR2> GetColliderVerticesInWorld();
    //RotateCollider(mat);
};
