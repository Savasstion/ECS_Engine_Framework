#include "Polygon2DColliderComponent.h"

#include "../BaseClasses/Entity.h"


Polygon2DColliderComponent::Polygon2DColliderComponent()
{
    Component(POLYGON2D_COLLIDER);
    this->colliderTag = ColliderTag::DEFAULT_COLLIDER;
}

std::vector<D3DXVECTOR2> Polygon2DColliderComponent::GetColliderVerticesInWorld()
{
    std::vector<D3DXVECTOR2> result;
    result.clear();

    for(auto v : vertices)
    {
        result.push_back(v + parent->transform->position + relativePos);
    }

    return result;
}
